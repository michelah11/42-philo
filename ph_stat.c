/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_stat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 04:01:11 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/09 01:28:14 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;
	bool	is_full;

	if (end_sim(philo->table) && status != DIED)
		return ;
	is_full = get_b(&philo->p_mx, &philo->full);
	if (is_full && status != DIED)
		return ;
	elapsed = gettime() - philo->table->start_t;
	if (pthread_mutex_lock(&philo->table->write_mtx) != 0)
		error_exit("Failed to lock write mutex in print_status");
	if (!end_sim(philo->table) || status == DIED)
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%ld %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING)
			printf("%ld %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING)
			printf("%ld %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING)
			printf("%ld %d is thinking\n", elapsed, philo->id);
		else if (status == DIED)
			printf("%ld %d has died\n", elapsed, philo->id);
	}
	if (pthread_mutex_unlock(&philo->table->write_mtx) != 0)
		error_exit("Failed to unlock write mutex in print_status");
}
