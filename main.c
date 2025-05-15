/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:14:35 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/15 22:58:33 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	terminate_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->ph_num)
	{
		destroy_mutex(&table->forks[i].fork);
		destroy_mutex(&table->philos[i].p_mx);
		i++;
	}
	destroy_mutex(&table->table_mtx);
	destroy_mutex(&table->write_mtx);
	free(table->philos);
	free(table->forks);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		input_parse(&table, av);
		init(&table);
		start(&table);
		terminate_philo(&table);
	}
	else
		error_exit("Wrong input:\nUsage: ./philo 6 800 300 300 [6]");
}
