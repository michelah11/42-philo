/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:14:35 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/21 22:38:07 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	clean(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->ph_num)
	{
		safe_mutex_handle(&table->forks[i].fork, DESTROY);
		safe_mutex_handle(&table->philos[i].p_mx, DESTROY);
		i++;
	}
	safe_mutex_handle(&table->table_mtx, DESTROY);
	safe_mutex_handle(&table->write_mtx, DESTROY);
	free(table->philos);
	free(table->forks);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		input_parse(&table, av);
		data_init(&table);
		dinner_start(&table);
		clean(&table);
	}
	else
	{
		error_exit("Wrong input:\nUsage: ./philo 6 800 300 300 [6]");
	}
}
