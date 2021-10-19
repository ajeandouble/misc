/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajean <ajeandouble42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:03:17 by ajean             #+#    #+#             */
/*   Updated: 2021/09/28 23:35:09 by ajean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_hexdump.h"

char	*alloc_final_final_buffer(void)
{
	char	*final_buffer;

	final_buffer = malloc(FILESIZE + 1);
	final_buffer[0] = '\0';
	return (final_buffer);
}

char	*clear_final_buffer(char *final_buffer)
{
	char	*new_buffer;

	free(final_buffer);
	new_buffer = alloc_final_final_buffer();
	return (new_buffer);
}
