#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned int l_ostack = 0;
unsigned int l_output = 0;

typedef struct s_token {
	char type;
	char op;
	int val;
} token;

token output[50]; // Output in RPN
token ostack[50]; // Operator stack

int ostack_push(token t) {
	printf("ostack_push %c %c to %d\n", t.type, t.op, l_output);
	ostack[l_ostack] = t;
	l_ostack++;
	return l_ostack;
}

int output_push(token t) {
	printf("output_push %c %d to %d\n", t.type, t.val, l_output);
	output[l_output] = t;
	l_output++;
	return l_output;
}

token output_pop() {
	if (l_output == 0) {
		token t;
		t.type = '\0';
	}
	return output[l_output--];
}

int ostack_pop() {
	printf("ostack_pop");
	if (!l_ostack)
		return 0;
	output[l_output] = ostack[l_ostack - 1];
	l_output++;
	l_ostack--;
}

char *clean_string(char *string) {
	int error = false;
	if (error)
		return NULL;
	return	(string);
}

bool gt_precedence(char op) {
	printf("op=>%c\n", op);
	if (l_ostack == 0) {
		printf("false\n");
		return false;
	}
	int top_ostack = l_ostack - 1;
	printf("top=%c\n", ostack[top_ostack].op);
	if (op == '+' || op == '-') {
		if (ostack[top_ostack].op == '*' || ostack[top_ostack].op == '/') {
			return true;
		}
	}
	return false;
}

int calculate(char op, int a, int b) {
	switch (op) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '/':
			return a / b;
		case '*':
			return a * b;
	}
}

void print_token(token t) {
	printf("[t=%c o=%c v=%d]", t.type, t.op, t.val);
}
int process_rpn() {
	token stack[50];
	int l_stack = 0;
	int i = 0;
	token t;
	printf("loutput=%d\n", l_output);
	while (i < l_output) {
		print_token(output[i]);
		t = output[i];
		if (t.type == 'n') {
			stack[l_stack++] = t;
		}
		else if (t.type == 'o') {	
			stack[l_stack - 2].val = calculate(t.op, stack[l_stack - 2].val, stack[l_stack - 1].val);

			printf("fuck%d=>%d", l_stack, stack[l_stack - 2].val);
			l_stack--;
		}
		int j = 0;
		printf("\n");
		while (j < l_stack) {
			printf("%d", i);			
			print_token(output[j++]);
		}	
		
		++i;
	}
	printf("\nl_stack=%d\noutput=%d\n", l_stack, stack[0].val	);
	return stack[0].val;
}
int eval(char *str) {
	int result = 0;

	while (*str) {
		// Numbers
		if ((*str >= '0' && *str <= '9') || (*str == '-')) {

			printf("atoi");
			int len_number = 0;
			while ((str[len_number] >= '0' && str[len_number] <= '9') || str[len_number] == '-') {
				++len_number;
			}

			// Add number token to output
			token number;
			number.type = 'n';
			number.val = atoi(str);
			printf("number_val=%d", number.val);
			output_push(number);

			str += len_number;
		}
		// Brackets
		else if (*str == '(' || * str == ')') {
			token br;
			br.type = 'b'; // bracket
			br.op = *str;
			if (*str == '(')
				ostack_push(br);
			else if (*str == ')') {
				while (ostack[l_ostack - 1].type != 'b' && ostack[l_ostack - 1].op != '(') {
					ostack_pop();
				}
				ostack_pop();
			}
			++str;
		}
		// Operators
		else {
			token op;
			op.type = 'o';
			op.op = *str;
			while (gt_precedence(op.op)) {
				printf("ostackpop\n");
				ostack_pop();	
			}
			ostack_push(op);
			
			//printf("operator:%c %c", *str, op.op);
			str++;
		}
	}

	while (l_ostack) {
		ostack_pop();
	}
	// print stacks:
	printf("\n");
	int i = 0;
	while (i < l_output) {
		token t;
		t = output[i];
		printf("[t=%c o=%c v=%d]", t.type, t.op, t.val);
		++i;
	}
	printf("\n");
	return process_rpn(); // result
	printf("ostack size=%d\n", l_ostack);
	return (result);
}

int main(int argc, char **argv) {
	if (argc != 2)
		return (-1);
	char *clean_str;
	if ((clean_str = clean_string(argv[1])) == NULL)
		return (-1);
	printf("Result for %s=%d", argv[1], eval(clean_str));
	return (0);
}


