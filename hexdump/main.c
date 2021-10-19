/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajean <ajeandouble42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 13:22:40 by ajean             #+#    #+#             */
/*   Updated: 2021/09/29 12:37:41 by ajean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ft_hexdump.h"

int	before_read_stdin(int ac, char **av)
{
	char	*final_buffer;

	if (ac == 1)
	{
		final_buffer = read_stdin(FALSE);
		ft_print_hex(final_buffer, FALSE, FALSE, 2);
		if (*final_buffer && ft_print_hex(final_buffer, FALSE, TRUE, 1))
			write(1, "\n", 1);
		free(final_buffer);
	}
	else if (ac == 2 && !ft_strcmp(av[1], "-C"))
	{
		final_buffer = read_stdin(TRUE);
		ft_print_hex(final_buffer, TRUE, FALSE, 2);
		if (*final_buffer && ft_print_hex(final_buffer, TRUE, TRUE, 2))
			write(1, "\n", 1);
		free(final_buffer);
	}
	else
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	if (before_read_stdin(ac, av))
		return (0);
	else if (ac >= 2 && ft_strcmp(av[1], "-C"))
		read_files(av[0], av + 1, ac - 1, FALSE);
	else if (ac > 2 && !ft_strcmp(av[1], "-C"))
		read_files(av[0], av + 2, ac - 2, TRUE);
	else
		write(1, "usage", 5);
	av = 0;
	return (0);
}
