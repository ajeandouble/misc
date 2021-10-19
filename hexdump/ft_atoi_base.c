/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajean <ajeandouble42@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:18:46 by ajean             #+#    #+#             */
/*   Updated: 2021/09/27 14:01:28 by ajean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	chr_in_base(char *base, char c)
{
	char	*start;

	start = base;
	while (*base)
	{
		if (c == *base)
			return (base - start);
		++base;
	}
	return (-1);
}

int	check_base(char *base)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-'
			|| (base[i] >= 9 && base[i] <= 13))
			return (-1);
		++i;
	}
	len = i;
	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
			if (base[i] == base[j++])
				return (-1);
		++i;
	}
	return (len);
}

int	ft_atoi_base(char *str, char *base)
{
	int	sign;
	int	result;
	int	base_len;

	if (check_base(base) <= 1)
		return (0);
	base_len = check_base(base);
	result = 0;
	sign = 1;
	while (*str == '\t' || *str == '\v'
		|| *str == '\r' || *str == '\f'
		|| *str == '\n' || *str == ' ')
		++str;
	while (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign *= -1;
	while (chr_in_base(base, *str) != -1)
	{
		result = (result * base_len) + chr_in_base(base, *str);
		++str;
	}
	return (result * sign);
}
