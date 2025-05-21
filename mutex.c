/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:39:40 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/21 22:30:07 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	handle_mutex_error(int status, t_code code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (code == LOCK || code == UNLOCK))
		error_exit("The value specified by mutex is invalid");
	else if (status == EINVAL && code == INIT)
		error_exit("The value specified by attribute is invalid");
	else if (status == EPERM)
		error_exit("The current thred does not hold a lock on mutex");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur");
	else if (status == ENOMEM)
		error_exit("Cannot allocate enough memory to create another mutex");
	else if (status == EBUSY)
		error_exit("Mutex is locked");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
	void *data, t_code code)
{
	if (code == CREATE)
		handle_mutex_error(pthread_create(thread, NULL, foo, data), code);
	else if (code == JOIN)
		handle_mutex_error(pthread_join(*thread, NULL), code);
	else if (code == DETACH)
		handle_mutex_error(pthread_detach(*thread), code);
	else
		error_exit("Wrong code for thread_handle");
}

void	safe_mutex_handle(t_mtx *mutex, t_code code)
{
	if (code == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), code);
	else
		error_exit("Wrong code for mutex handle");
}
