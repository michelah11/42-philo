/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 04:01:11 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/21 22:40:50 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	if (philo->full)
		return ;
	safe_mutex_handle(&philo->table->write_mtx, LOCK);
	elapsed = gettime() - philo->table->start_t;
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !end_sim(philo->table))
		printf("%ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && !end_sim(philo->table))
		printf("%ld %d is eating\n", elapsed, philo->id);
	else if (status == SLEEPING && !end_sim(philo->table))
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !end_sim(philo->table))
		printf("%ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%ld %d has died\n", elapsed, philo->id);
	safe_mutex_handle(&philo->table->write_mtx, UNLOCK);
}
