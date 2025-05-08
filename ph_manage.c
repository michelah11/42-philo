/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 05:17:30 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/09 01:30:17 by mabou-ha         ###   ########.fr       */
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
	print_status(DIED, philo);
	return ;
}

static bool kill_cond(t_table *table, t_philo *philo)
{
	long now = gettime();
	long last_meal = get_l(&philo->p_mx, &philo->lmeal_t);
	if (last_meal == 0)
		return false;
	return (!get_b(&philo->p_mx, &philo->full) &&
			(now - last_meal >= table->die_t / 1000));
}

void	*manage_dinner(void *arg)
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
