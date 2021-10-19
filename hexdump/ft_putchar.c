/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajean <ajeandouble42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:43:53 by ajean             #+#    #+#             */
/*   Updated: 2021/09/27 17:05:13 by ajean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_hexdump.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putchar_hex(char c)
{
	char	*base;

	base = HEX_BASE;
	ft_putchar(base[c / 16]);
	ft_putchar(base[c % 16]);
}
