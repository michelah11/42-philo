/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:18:14 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/09 00:24:36 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_b(t_mtx *mutex, bool *dest, bool value)
{
	if (pthread_mutex_lock(mutex) != 0)
		error_exit("Failed to lock mutex in set_b");
	*dest = value;
	if (pthread_mutex_unlock(mutex) != 0)
		error_exit("Failed to unlock mutex in set_b");
}

bool	get_b(t_mtx *mutex, bool *value)
{
	bool	ret;

	if (pthread_mutex_lock(mutex) != 0)
		error_exit("Failed to lock mutex in get_b");
	ret = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		error_exit("Failed to unlock mutex in get_b");
	return (ret);
}

void	set_l(t_mtx *mutex, long *dest, long value)
{
	if (pthread_mutex_lock(mutex) != 0)
		error_exit("Failed to lock mutex in set_l");
	*dest = value;
	if (pthread_mutex_unlock(mutex) != 0)
		error_exit("Failed to unlock mutex in set_l");
}

long	get_l(t_mtx *mutex, long *value)
{
	long	ret;

	if (pthread_mutex_lock(mutex) != 0)
		error_exit("Failed to lock mutex in get_l");
	ret = *value;
	if (pthread_mutex_unlock(mutex) != 0)
		error_exit("Failed to unlock mutex in get_l");
	return (ret);
}

bool	end_sim(t_table *table)
{
	return (get_b(&table->table_mtx, &table->sim_end));
}
