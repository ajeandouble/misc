/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajean <ajeandouble42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:10:13 by ajean             #+#    #+#             */
/*   Updated: 2021/09/29 12:50:37 by ajean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_hexdump.h"

int	ft_putnbr_base(t_uli lnb, t_bool arg, char *base)
{
	char		result[100];
	short int	i;
	int			base_len;
	int			len;

	base_len = ft_strlen(base);
	result[0] = base[0];
	i = 0;
	if (0 == lnb)
		i = 1;
	while (lnb)
	{
		result[i++] = base[lnb % base_len];
		lnb /= base_len;
	}
	len = 8 + arg - i - 1;
	while (len--)
		write(1, "0", 1);
	while (--i >= 0)
		write(1, result + i, 1);
	return (1);
}

void	padding(int n, t_bool arg, t_bool last_line)
{
	if (n)
		n = 16 - n;
	if (n && !arg)
	{
		while (n-- > 1)
			write(1, "    ", 3);
		write(1, "       ", 2);
	}
	if (n && arg && last_line)
	{
		write(1, " ", 1);
	}
}
