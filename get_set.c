/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:18:14 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/15 22:44:37 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_b(t_mtx *mutex, bool *dest, bool value)
{
	lock_mtx(mutex);
	*dest = value;
	unlock_mtx(mutex);
}

bool	get_b(t_mtx *mutex, bool *value)
{
	bool	ret;

	lock_mtx(mutex);
	ret = *value;
	unlock_mtx(mutex);
	return (ret);
}

void	set_l(t_mtx *mutex, long *dest, long value)
{
	lock_mtx(mutex);
	*dest = value;
	unlock_mtx(mutex);
}

long	get_l(t_mtx *mutex, long *value)
{
	long	ret;

	lock_mtx(mutex);
	ret = *value;
	unlock_mtx(mutex);
	return (ret);
}

bool	end_sim(t_table *table)
{
	return (get_b(&table->table_mtx, &table->sim_end));
}
