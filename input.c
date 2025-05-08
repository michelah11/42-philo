/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:24:05 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/09 00:19:40 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static const char	*validation(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (ft_isspace((int)*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_exit("Only postive values are accepted");
	if (!(*str >= 48 && *str <= 57))
		error_exit("Only numerical input is accepted");
	number = str;
	while (*str >= 48 && *str++ <= 57)
		len++;
	if (len > 10)
		error_exit("Numerical value unaccepted");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = validation(str);
	while (*str >= 48 && *str <= 57)
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_exit("Numerical value unaccepted");
	return (num);
}

void	input_parse(t_table *table, char **av)
{
	table->ph_num = ft_atol(av[1]);
	table->die_t = ft_atol(av[2]) * 1000;
	table->eat_t = ft_atol(av[3]) * 1000;
	table->sleep_t = ft_atol(av[4]) * 1000;
	if (table->die_t < 60000 || table->eat_t < 60000
		|| table->sleep_t < 60000)
		error_exit("Input time less than 60ms");
	if (av[5])
		table->meal_limit = ft_atol(av[5]);
	else
		table->meal_limit = -1;
}
