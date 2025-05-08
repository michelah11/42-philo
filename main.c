/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:14:35 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/07 04:31:07 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	terminate_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->ph_num)
	{
		if (pthread_mutex_destroy(&table->forks[i].fork) != 0)
			error_exit("Failed to destroy fork mutex");
		if (pthread_mutex_destroy(&table->philos[i].p_mx) != 0)
			error_exit("Failed to destroy philosopher mutex");
		i++;
	}
	if (pthread_mutex_destroy(&table->table_mtx) != 0)
		error_exit("Failed to destroy table mutex");
	if (pthread_mutex_destroy(&table->write_mtx) != 0)
		error_exit("Failed to destroy write mutex");
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
