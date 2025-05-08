/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 01:34:23 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/07 04:27:35 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philo_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		error_exit("No allocation made");
	return (ret);
}
