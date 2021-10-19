/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajean <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:18:48 by ajean             #+#    #+#             */
/*   Updated: 2021/09/28 23:18:48 by ajean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ft_hexdump.h"

char	*make_buffer(int *read_len, char *array)
{
	char	*final_buffer;

	final_buffer = alloc_final_final_buffer();
	*read_len = read(0, array, FILESIZE);
	return (final_buffer);
}

char	*read_stdin(t_bool arg)
{
	char	array[FILESIZE + 1];
	int		read_len;
	char	*final_buffer;
	int		total_len;

	final_buffer = make_buffer(&read_len, array);
	if (read_len == -1)
		return (0);
	total_len = read_len;
	array[read_len] = '\0';
	final_buffer = ft_strncat_realloc(final_buffer, array, read_len);
	while (read_len > 0)
	{
		if (total_len >= 16 && ft_print_hex(final_buffer, arg, FALSE, 1))
		{
			final_buffer = clear_final_buffer(final_buffer);
			total_len = 0;
		}
		read_len = read(0, array, FILESIZE);
		array[read_len] = '\0';
		final_buffer = ft_strncat_realloc(final_buffer, array, read_len);
		total_len += read_len;
	}
	return (final_buffer);
}
