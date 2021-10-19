/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajean <ajeandouble42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 13:45:57 by ajean             #+#    #+#             */
/*   Updated: 2021/09/29 12:50:41 by ajean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_hexdump.h"

t_bool	print_addr(t_uli line_number, t_bool arg, t_bool last_addr, char *b)
{
	(void)b;
	if (*b)
		ft_putnbr_base(line_number, arg, HEX_BASE);
	if (!last_addr)
	{
		write(1, "  ", 1 + arg);
	}
	return (TRUE);
}

static inline int	print_hex_line(char *line, t_bool arg)
{
	int	i;

	i = 0;
	while (line[i] && i < 16)
	{
		ft_putchar_hex(line[i]);
		if (arg || i != 15)
			ft_putstr(" ");
		if (arg && i == 7)
			ft_putstr(" ");
		++i;
	}
	return (i % 16);
}

int	skip_duplicates(char *buffer, t_uli *addr)
{
	int	i;
	int	len;

	len = ft_strlen(buffer);
	i = 0;
	while (i <= len - 16 && !ft_strncmp(buffer + i, buffer + i + 16, 16))
		i += 16;
	if (i)
		ft_putstr("*\n");
	*addr += i;
	return (i);
}

int	print_ascii(char *line)
{
	int	i;
	int	pad;
	int	len;

	len = 16;
	if (ft_strlen(line) < 16)
		len = ft_strlen(line);
	i = 0;
	pad = 16 - len;
	while (pad--)
		ft_putstr("   ");
	ft_putchar('|');
	while (i < len)
	{
		if (line[i] >= 32 && line[i] <= 126)
			ft_putchar(line[i]);
		else
			ft_putchar('.');
		++i;
	}
	ft_putchar('|');
	return (1);
}

t_bool	ft_print_hex(char *b, t_bool arg, t_bool last_addr, int s)
{
	static t_uli	addr = 0;
	static t_uli	total_len = 0;
	t_uli			i;
	t_uli			len;

	len = ft_strlen(b);
	if (last_addr == TRUE
		&& print_addr(addr + total_len / s % 16, arg, last_addr, b))
		return (TRUE);
	total_len += len;
	i = 0;
	while (i < len)
	{
		print_addr(addr, arg, last_addr, b);
		padding(print_hex_line(b + i, arg), arg, len - i < 16);
		if (arg && ft_putstr(" "))
			print_ascii(b + i);
		ft_putstr("\n");
		if (len >= 32)
			i += skip_duplicates(b + i, &addr);
		if (addr + 16 < len)
			addr += 16;
		i += 16;
	}
	return (TRUE);
}
