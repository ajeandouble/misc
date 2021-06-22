#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

 #define max(a,b) \
	({ __typeof__ (a) _a = (a); \
		__typeof__ (b) _b = (b); \
		_a > _b ? _a : _b; })

#define min(a,b) \
	({ __typeof__ (a) _a = (a); \
		__typeof__ (b) _b = (b); \
		_a < _b ? _a : _b; })


typedef struct s_output { unsigned short back; unsigned short size; char c; } s_output;

#define BUFF_SIZE 1024
#define SEARCH_BUFFER 15
#define LOOK_AHEAD 6

static char *concat_output;

static size_t find_matches(s_output *output, size_t output_index, char *str, size_t str_index, size_t len) {
	size_t max_lookahead = LOOK_AHEAD;
	size_t max_search_buffer = SEARCH_BUFFER;

	/* PSEUDO_CODE
		if output + i - max_search_buffer < output
			start_output = output
		else:
			start_output = &[output[i] - max_search_buffer

		strdup from (start_output->c to output[i].c)
		strdup from (str + i to min(str + end, str + look_ahead) 
		while i + lookahead < len AND i <= lookahead
			si strnstr(start_output, &str[i], lookahead)
				result = { }

	*/
	s_output *start_output = max(output, &output[output_index - max_search_buffer]);
	size_t concat_output_len = (size_t)(&output[output_index] - start_output); // MINIMUM 1
	concat_output = malloc(sizeof (char) * (concat_output_len + 1));
	bzero(concat_output, sizeof (char) * (concat_output_len + 1));

	for (size_t i = 0; i < concat_output_len && &start_output[i] < &output[output_index]; i++) {
		concat_output[i] = start_output[i].c;
	}

	#ifdef DEBUG
		printf("concat_output:\t%s\nconcat_output_len=%d\n", concat_output, concat_output_len);
	#endif

	s_output output_elem = (s_output) { .c = '\0', .back = 0, .size = 0 };
	char *found_str = NULL;
	size_t found_str_len = 0;
	for (size_t lookahead = 1; lookahead <= max_lookahead && str_index + lookahead < len && start_output + lookahead <= &output[output_index]; ++lookahead) {
		char *str2 = strndup(&str[str_index], lookahead);
		printf("concat_output2:%s\tstr2:%s\n", concat_output, str2);
		found_str = strstr(concat_output, str2);

		if (NULL == found_str)
			break;
		found_str_len = strlen(found_str);
		output_elem.c = str[str_index + lookahead];

		output_elem.back = concat_output_len - (size_t)(found_str - concat_output); // debug but tired
		output_elem.size = lookahead;

		#ifdef DEBUG
			// printf("(%s)%c\n", str2, str[str_index]);
			printf("%c %u %u", output_elem.c, output_elem.back, output_elem.size);
		#endif
	}
	if (NULL == found_str_len) {
		printf("not found:");
		output[output_index] = (s_output) { .c = str[str_index ], .back = 0, .size = 0 };
		printf("%c\n", output[output_index].c);
	}
	else {
		output[output_index] = (s_output) output_elem;
	}
	return(max(output[output_index].size + 1, 1)); 
}

char *encode(s_output output[], size_t len) {
	char *encoded_str = malloc(sizeof(output[0]) * len);

	size_t i = 0;
	size_t j = 0;
	while (i < len) {
		encoded_str[j] = (0xFF & output[i].back) ;
		printf("%x", encoded_str[j]);
		encoded_str[j+1] = (output[i].back >> 8) & 0xFF;
		printf("%x", encoded_str[j+1]);

		encoded_str[j+2] = 0xFF & output[i].size;
		printf("%x", encoded_str[j+2]);
		encoded_str[j+3] = 0xFF & (output[i].size >> 8);
		printf("%x", encoded_str[j+3]);
		encoded_str[j+4] = output[i].c;
		printf("%c", encoded_str[j+4]);
		
		j += 5;
		i++;
	}
	for (i = 0; i < len * 5; i++)
		printf("%x", encoded_str[i]);
	return (encoded_str);
}

char *compress(char *str ) {
	#define MAX_SIZE strlen(str) + 1

	s_output output[MAX_SIZE];
	memset(output, 0, sizeof(output[0]) * MAX_SIZE); 
	output[0] = (s_output) { .c = str[0] };

	size_t len = strlen(str);
	concat_output = (char *)malloc(sizeof(char) * len + sizeof(char));
	bzero(concat_output, len);

	size_t output_index = 1;
	size_t i = 1;
	output[0] = (s_output) { .c = str[0] };
	while (str[i]) {
		i += find_matches(output, output_index++, str, i, len);
	}

	#ifdef DEBUG

	{
		size_t i = 0;
		while (i < MAX_SIZE) {
			printf("output[%u]\t%c\tback:%u\tsize:%u\n", i, output[i].c, output[i].back, output[i].size);
			++i;
		}
	}

	#endif

	#ifdef DEBUG

	{
		#define HYPHENS(n) { char array[n] = { [0 ... n-2] = '-'}; printf("%s\n", array); };
		printf("DECODED_STR\n");
		char decoded_str[5000000];
		size_t i = 0;
		size_t j = 0;
		while (i < MAX_SIZE) {
			if (output[i].size == 0 && output[i].back == 0) {
				decoded_str[j++] = output[i].c;
			}
			else {
				size_t k = 0;
				while (k < output[i].size) {
					decoded_str[j+k] = output[i+k-output[i].back].c;
					k++;
				}
				j += k;
				decoded_str[j++] = output[i].c;
			}
			++i;
		}
		printf("%s\n", decoded_str);
		printf("%s=%s?->%s\n", str, decoded_str, !strcmp(str, decoded_str) ? "GOOD" : "FALSE");
		HYPHENS(80);
	}

	#endif
	char *encoded_str = encode(output, MAX_SIZE);
	return (encoded_str);
}

char *decompress(char *str ) {
	return (str);	
}

char *read_file(FILE *file) {
	fseek(file, 0, SEEK_END);
	size_t file_size = ftell(file); // get current file pointer
	fseek(file, 0, SEEK_SET);

	char *input_buffer = (char *)malloc(file_size* sizeof(char) + 1);
	if (NULL == input_buffer) {
		perror(NULL);
		exit (-1);
	}
	size_t len;
	size_t ret = 0;
	while ((ret = fread(input_buffer + len, BUFF_SIZE, 1, file))) {
		len += ret * BUFF_SIZE;
	}

	input_buffer[file_size] = '\0';
	return (input_buffer);
}

int main(int ac, char **av) {
	FILE *input_file;

	if (ac == 1)
		input_file = stdin;
	else if (ac != 3 || (strcmp(av[1], "-c") && strcmp(av[1], "-d") ) ) {
		fprintf(stderr, "usage: lz (-c | -d) <input_file>\n");
		exit (-1);
  	} 
	else {
		input_file = fopen(av[2], "r");
	}

	if (NULL == input_file) {
		perror(av[2]);
	}
	char *str = read_file(input_file);
	switch (av[1][1]) {
		case 'c':
			str = compress(str);
			break;
		case 'd':
			str = decompress(str);
			break;
	}

	printf("%s", str);
	return (0);
}
