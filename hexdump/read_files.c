/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajean <ajeandouble42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 23:18:41 by ajean             #+#    #+#             */
/*   Updated: 2021/09/28 23:30:57 by ajean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ft_hexdump.h"

void	read_first_buffer(t_file *f, char *path, char *program_name)
{
	f->fd = open(path, O_RDONLY);
	ft_print_error(program_name, path);
	f->read_len = read(f->fd, f->array, FILESIZE);
}

void	keep_reading(t_file *f)
{
	f->total_len += f->read_len;
	f->array[f->read_len] = '\0';
	f->fb = ft_strncat_realloc(f->fb, f->array, f->read_len);
	while (f->read_len > 0)
	{
		f->read_len = read(f->fd, f->array, FILESIZE);
		f->total_len += f->read_len;
		f->array[f->read_len] = '\0';
		f->fb = ft_strncat_realloc(f->fb, f->array, f->read_len);
	}
}

void	print_hex(t_file f, t_bool arg)
{
	ft_print_hex(f.fb, arg, FALSE, 1);
	ft_print_hex(f.fb, arg, TRUE, 1);
	if (*(f.fb))
		write(1, "\n", 1);
	free(f.fb);
}

int	read_files(char *program_name, char **paths, int n_files, t_bool arg)
{
	t_file	f;
	int		i;

	f.fb = alloc_final_final_buffer();
	i = 0;
	while (i < n_files)
	{
		read_first_buffer(&f, paths[i], program_name);
		if ((f.fd == -1 || f.read_len == -1)
			&& ft_print_error(program_name, paths[i]) && ++i)
		{
			f.array[0] = '\0';
			f.read_len = 0;
			if (f.fd != -1)
				close (f.fd);
			continue ;
		}
		keep_reading(&f);
		close(f.fd);
		++i;
	}
	if (f.fb && f.read_len != -1)
		print_hex(f, arg);
	return (1);
}
