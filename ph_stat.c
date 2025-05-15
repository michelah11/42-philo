/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_stat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 04:01:11 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/15 23:38:33 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	lock_mtx(&philo->table->write_mtx);
	elapsed = gettime() - philo->table->start_t;
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
	unlock_mtx(&philo->table->write_mtx);
}
