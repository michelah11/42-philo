/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:06:55 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/09 01:31:15 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	one_ph(t_philo *p)
{
	sleep_th(p->table->die_t, p->table);
	if (pthread_mutex_unlock(&p->first_fork->fork) != 0)
		error_exit("Failed to unlock first fork");
	while (!end_sim(p->table))
		usleep(100);
	return ;
}

void	eat(t_philo *p)
{
	if (p->id % 2 == 0)
		usleep(100);
	if (pthread_mutex_lock(&p->first_fork->fork) != 0)
		error_exit("Failed to lock first fork");
	print_status(TAKE_FIRST_FORK, p);
	if (p->table->ph_num == 1)
	{
		one_ph(p);
		return ;
	}
	if (pthread_mutex_lock(&p->second_fork->fork) != 0)
		error_exit("Failed to lock second fork");
	print_status(TAKE_SECOND_FORK, p);
	set_l(&p->p_mx, &p->lmeal_t, gettime());
	p->meal_count++;
	print_status(EATING, p);
	sleep_th(p->table->eat_t, p->table);
	if (pthread_mutex_unlock(&p->second_fork->fork) != 0)
		error_exit("Failed to unlock second fork");
	if (pthread_mutex_unlock(&p->first_fork->fork) != 0)
		error_exit("Failed to unlock first fork");
	if (p->table->meal_limit > 0 && p->meal_count == p->table->meal_limit)
		set_b(&p->p_mx, &p->full, true);
}

void	*sim(void *arg)
{
	t_philo	*philo;

	philo = arg;
	threads_wait(philo->table);
	while (!end_sim(philo->table))
	{
		if (get_b(&philo->p_mx, &philo->full))
			break ;
		if (!end_sim(philo->table))
			eat(philo);
		if (!end_sim(philo->table))
		{
			print_status(SLEEPING, philo);
			sleep_th(philo->table->sleep_t, philo->table);
		}
		if (!end_sim(philo->table))
			print_status(THINKING, philo);
	}
	return (NULL);
}

static void time_s(t_table *t)
{
	long	start;
	
	start = gettime();
	while (gettime() - start < 1)
        usleep(10);
    t->start_t = gettime();
}

void	start(t_table *t)
{
	int			i;
	pthread_t	manage;

	if (t->meal_limit == 0)
		return ;
	i = 0;
	while (i < t->ph_num)
	{
		if (pthread_create(&t->philos[i].th_id, NULL, sim, &t->philos[i]) != 0)
			error_exit("Failed to create philosopher thread");
		i++;
	}
	time_s(t);
	set_b(&t->table_mtx, &t->th_ready, true);
	if (pthread_create(&manage, NULL, manage_dinner, t) != 0)
		error_exit("Failed to create manage thread");
	if (pthread_join(manage, NULL) != 0)
		error_exit("Failed to join manage thread");
	i = 0;
	while (i < t->ph_num)
	{
		if (pthread_join(t->philos[i].th_id, NULL) != 0)
			error_exit("Failed to join philosopher thread");
		i++;
	}
}
