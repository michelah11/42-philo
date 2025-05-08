/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:33:08 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/09 01:46:18 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int ph_pos)
{
	int right = (ph_pos + 1) % philo->table->ph_num;

    if (ph_pos < right)
    {
        philo->first_fork = &forks[ph_pos];
        philo->second_fork = &forks[right];
    }
    else
    {
        philo->first_fork = &forks[right];
        philo->second_fork = &forks[ph_pos];
    }
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->ph_num)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meal_count = 0;
		philo->lmeal_t = 0;
		philo->table = table;
		if (pthread_mutex_init(&philo->p_mx, NULL) != 0)
			error_exit("Failed to initialize philosopher mutex");
		assign_forks(philo, table->forks, i);
		i++;
	}
}

void	init(t_table *table)
{
	int	i;

	i = 0;
	table->sim_end = false;
	table->th_ready = false;
	table->n_th_running = 0;
	table->philos = philo_malloc(sizeof(t_philo) * table->ph_num);
	if (pthread_mutex_init(&table->table_mtx, NULL) != 0)
		error_exit("Failed to initialize table mutex");
	if (pthread_mutex_init(&table->write_mtx, NULL) != 0)
		error_exit("Failed to initialize write mutex");
	table->forks = philo_malloc(sizeof(t_fork) * table->ph_num);
	while (i < table->ph_num)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			error_exit("Failed to initialize fork mutex");
		i++;
	}
	philo_init(table);
}
