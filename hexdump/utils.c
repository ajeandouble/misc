/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajean <ajeandouble42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 13:02:57 by ajean             #+#    #+#             */
/*   Updated: 2021/09/28 18:47:36 by ajean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libgen.h>
#include "ft_hexdump.h"

int	print_usage(char *program_name)
{
	ft_putstr_fd(basename(program_name), 2);
	ft_putstr_fd(": option requires an argument -- c\n", 2);
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(basename(program_name), 2);
	ft_putstr_fd(" [-F | -f | -r] [-q] [-b # | -c # | -n #]", 2);
	ft_putstr_fd("[file ...]\n", 2);
	return (1);
}
