/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:33:08 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/15 22:54:11 by mabou-ha         ###   ########.fr       */
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
		init_mutex(&philo->p_mx);
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
	init_mutex(&table->table_mtx);
	init_mutex(&table->write_mtx);
	table->forks = philo_malloc(sizeof(t_fork) * table->ph_num);
	while (i < table->ph_num)
	{
		init_mutex(&table->forks[i].fork);
		i++;
	}
	philo_init(table);
}
