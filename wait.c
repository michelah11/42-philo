/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 04:32:17 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/09 01:31:53 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	threads_wait(t_table *table)
{
	while (!get_b(&table->table_mtx, &table->th_ready) && !end_sim(table))
		usleep(100);
}
