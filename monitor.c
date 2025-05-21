/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 05:17:30 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/21 22:40:39 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_meal_limit(t_table *table, int count)
{
	if (table->meal_limit > 0 && count == table->ph_num)
		set_b(&table->table_mtx, &table->sim_end, true);
	return ;
}

static void	philo_die(t_table *table, t_philo *philo)
{
	set_b(&table->table_mtx, &table->sim_end, true);
	write_status(DIED, philo);
	return ;
}

static bool	kill_cond(t_table *table, t_philo *philo)
{
	long	now;

	now = gettime();
	return (!get_b(&philo->p_mx, &philo->full)
		&& (now - get_l(&philo->p_mx, &philo->lmeal_t) > table->die_t / 1000));
}

void	*monitor_dinner(void *arg)
{
	t_table	*t;
	int		i;
	int		full_count;

	t = (t_table *)arg;
	while (!get_b(&t->table_mtx, &t->sim_end))
	{
		full_count = 0;
		i = 0;
		while (i < t->ph_num)
		{
			if (get_l(&t->philos[i].p_mx, &t->philos[i].lmeal_t) == 0)
				set_l(&t->philos[i].p_mx, &t->philos[i].lmeal_t, t->start_t);
			if ((kill_cond(t, &t->philos[i])))
			{
				philo_die(t, &t->philos[i]);
				return (NULL);
			}
			if (get_b(&t->philos[i].p_mx, &t->philos[i].full))
				full_count++;
			i++;
		}
		check_meal_limit(t, full_count);
	}
	return (NULL);
}
