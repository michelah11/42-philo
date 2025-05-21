/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:33:08 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/21 22:35:49 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int ph_pos)
{
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[ph_pos];
		philo->second_fork = &forks[(ph_pos + 1) % philo->table->ph_num];
	}
	else
	{
		philo->first_fork = &forks[(ph_pos + 1) % philo->table->ph_num];
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
		safe_mutex_handle(&philo->p_mx, INIT);
		assign_forks(philo, table->forks, i);
		i++;
	}
}

void	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->sim_end = false;
	table->th_ready = false;
	table->n_th_running = 0;
	table->philos = philo_malloc(sizeof(t_philo) * table->ph_num);
	safe_mutex_handle(&table->table_mtx, INIT);
	safe_mutex_handle(&table->write_mtx, INIT);
	table->forks = philo_malloc(sizeof(t_fork) * table->ph_num);
	while (i < table->ph_num)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
	}
	philo_init(table);
}
