/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:06:55 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/15 23:36:59 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	one_ph(t_philo *p)
{
	sleep_th(p->table->die_t, p->table);
	lock_mtx(&p->first_fork->fork);
	sleep_th(p->table->die_t, p->table);
	philo_die(p->table, p);
	return ;
}

void	eat(t_philo *p)
{
	if (p->id % 2 == 0)
		usleep(100);
	lock_mtx(&p->first_fork->fork);
	print_status(TAKE_FIRST_FORK, p);
	if (p->table->ph_num == 1)
	{
		one_ph(p);
		return ;
	}
	lock_mtx(&p->second_fork->fork);
	print_status(TAKE_SECOND_FORK, p);
	set_l(&p->p_mx, &p->lmeal_t, gettime());
	p->meal_count++;
	print_status(EATING, p);
	sleep_th(p->table->eat_t, p->table);
	unlock_mtx(&p->second_fork->fork);
	unlock_mtx(&p->first_fork->fork);
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
		create_thread(&t->philos[i].th_id, sim, &t->philos[i]);
		i++;
	}
	time_s(t);
	set_b(&t->table_mtx, &t->th_ready, true);
	create_thread(&manage, manage_dinner, t);
	join_thread (manage);
	i = 0;
	while (i < t->ph_num)
	{
		join_thread (t->philos[i].th_id);;
		i++;
	}
}
