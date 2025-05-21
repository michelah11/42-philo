/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:15:31 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/21 23:30:05 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;

	start = gettime();
	usleep(usec * 0.9);
	while (!end_sim(table) && gettime() - start < usec / 1000)
		usleep(10);
}

long	gettime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Getting time failed");
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}
