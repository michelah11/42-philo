/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:07:29 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/15 23:10:18 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_thread(pthread_t *t, void *(*f) (void *),void *arg)
{
	if (pthread_create(t, NULL, f, arg) != 0)
		error_exit("Failed to create thread");
	return;
}

void	join_thread (pthread_t t)
{
	if (pthread_join(t, NULL) != 0)
		error_exit("Failed to join thread");
}