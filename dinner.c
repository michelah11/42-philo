/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:06:55 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/21 22:30:02 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static void	ft_usleep(long sleep)
// {
// 	long	curtime;

// 	curtime = gettime(MILLISECOND);
// 	usleep(sleep * 0.9);
// 	while (gettime(MILLISECOND) - curtime < sleep /1000)
// 		usleep(50);
// }

void	eat(t_philo *p)
{
	safe_mutex_handle(&p->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, p);
	if (p->table->ph_num == 1)
	{
		precise_usleep(p->table->die_t + 1, p->table);
		safe_mutex_handle(&p->first_fork->fork, UNLOCK);
		while (!end_sim(p->table))
			usleep(10);
		return ;
	}
	safe_mutex_handle(&p->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, p);
	set_l(&p->p_mx, &p->lmeal_t, gettime(MILLISECOND));
	p->meal_count++;
	write_status(EATING, p);
	precise_usleep(p->table->eat_t, p->table);
	safe_mutex_handle(&p->second_fork->fork, UNLOCK);
	safe_mutex_handle(&p->first_fork->fork, UNLOCK);
	if (p->table->meal_limit > 0 && p->meal_count == p->table->meal_limit)
		set_b(&p->p_mx, &p->full, true);
}

void	*dinner_sim(void *arg)
{
	t_philo	*philo;

	philo = arg;
	wait_all_threads(philo->table);
	while (!end_sim(philo->table))
	{
		if (get_b(&philo->p_mx, &philo->full))
			break ;
		if (!end_sim(philo->table))
			eat(philo);
		if (!end_sim(philo->table))
		{
			write_status(SLEEPING, philo);
			precise_usleep(philo->table->sleep_t, philo->table);
		}
		if (!end_sim(philo->table))
			write_status(THINKING, philo);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	if (table->meal_limit == 0)
		return ;
	table->start_t = gettime(MILLISECOND);
	set_b(&table->table_mtx, &table->th_ready, true);
	i = 0;
	while (i < table->ph_num)
	{
		safe_thread_handle(&table->philos[i].thread_id, dinner_sim,
			&table->philos[i], CREATE);
		i++;
	}
	safe_thread_handle(&monitor_thread, monitor_dinner, table, CREATE);
	safe_thread_handle(&monitor_thread, NULL, NULL, JOIN);
	i = 0;
	while (i < table->ph_num)
	{
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}
