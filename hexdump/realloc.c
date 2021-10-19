/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajean <ajeandouble42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:23:18 by ajean             #+#    #+#             */
/*   Updated: 2021/09/28 23:29:36 by ajean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_hexdump.h"

void	saved_to_final(char **f_buffer, char **saved_fb, int len, t_uli *index)
{
	int	i;

	i = 0;
	while (i < len)
	{
		f_buffer[0][i] = saved_fb[0][i];
		++i;
	}
	*index = i;
}

void	total_len_leq_size(int i, int total_len, char **f_buffer, char *array)
{
	int	j;

	j = 0;
	while (i < total_len)
		f_buffer[0][i++] = array[j++];
	f_buffer[0][i] = '\0';
}

char	*ft_strncat_realloc(char *f_buffer, char *array, int l)
{
	static unsigned long int	total_len = 0;
	static unsigned long int	size = FILESIZE;
	char						*saved_final_buffer;
	unsigned long int			i;
	int							j;

	total_len += l;
	if (total_len > size)
	{
		size *= 2;
		saved_final_buffer = f_buffer;
		f_buffer = malloc(sizeof(char) * size + 1);
		saved_to_final(&f_buffer, &saved_final_buffer, total_len - l, &i);
		j = 0;
		while (i < total_len)
			f_buffer[i++] = array[j++];
		f_buffer[i] = '\0';
		free(saved_final_buffer);
	}
	else
		total_len_leq_size(total_len - l, total_len, &f_buffer, array);
	return (f_buffer);
}
