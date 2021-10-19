/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstrs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajean <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:17:43 by ajean             #+#    #+#             */
/*   Updated: 2021/09/28 23:17:45 by ajean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include "ft_hexdump.h"

void	ft_putstr_fd(char *str, int fd)
{
	char	*start;

	start = str;
	while (*str)
		++str;
	write(fd, start, str - start);
}

int	ft_putstr(char *str)
{
	char	*start;

	start = str;
	while (*str)
		++str;
	write(1, start, str - start);
	return (1);
}

void	ft_putnstr_fd(char *str, int size, int fd)
{
	char	*start;
	int		i;

	i = 0;
	start = str;
	while (*str && i < size)
	{
		++str;
		++i;
	}
	write(fd, start, i);
}

void	ft_putnstr(char *str, int size)
{
	char	*start;
	int		i;

	i = 0;
	start = str;
	while (*str && i < size)
	{
		++str;
		++i;
	}
	write(1, start, i);
}

int	ft_print_error(char *program_name, char *path)
{
	if (errno == 0)
		return (0);
	ft_putstr_fd(basename(program_name), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	errno = 0;
	return (1);
}
