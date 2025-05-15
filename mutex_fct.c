/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:36:02 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/15 23:15:48 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_mtx(t_mtx *mtx)
{
	char	*str;

	str = "Failed to lock mutex";
	if (pthread_mutex_lock(mtx) != 0)
		error_exit(str);
	return ;
}

void	unlock_mtx(t_mtx *mtx)
{
	char	*str;

	str = "Failed to unlock mutex";
	if (pthread_mutex_unlock(mtx) != 0)
		error_exit(str);
	return ;
}

void	init_mutex(t_mtx *mtx)
{
	if (pthread_mutex_init(mtx, NULL) != 0)
		error_exit("Failed to initialize mutex");
	return ;
}

void	destroy_mutex(t_mtx *mtx)
{
	if (pthread_mutex_destroy(mtx) != 0)
			error_exit("Failed to destroy mutex");
	return ;
}
