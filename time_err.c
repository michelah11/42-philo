/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:15:31 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/09 01:31:44 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void	sleep_th(long usec, t_table *table)
{
	long	start;
	long	rem;

	start = gettime();
	rem = usec / 1000;
	while (!end_sim(table) && (gettime() - start) < rem)
		usleep(100);
}

long	gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		error_exit("Getting time failed");
		return (0);
	}
	else
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}
