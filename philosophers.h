/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabou-ha <mabou-ha@@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:58:03 by mabou-ha          #+#    #+#             */
/*   Updated: 2025/05/21 23:29:53 by mabou-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED
}	t_philo_status;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_time_code;

typedef enum e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_code;

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	int				meal_count;
	bool			full;
	long			lmeal_t;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	t_mtx			p_mx;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	long		ph_num;
	long		die_t;
	long		eat_t;
	long		sleep_t;
	long		meal_limit;
	long		start_t;
	long		n_th_running;
	bool		sim_end;
	bool		th_ready;
	pthread_t	monitor;
	t_mtx		table_mtx;
	t_mtx		write_mtx;
	t_fork		*forks;
	t_philo		*philos;
}	t_table;

//utils.c
void	error_exit(const char *error);
long	gettime(void);
void	precise_usleep(long usec, t_table *table);
//alloc.c
void	*philo_malloc(size_t size);
//mutex.c
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_code opcode);
void	safe_mutex_handle(t_mtx *mutex, t_code code);
// data_init.c
void	data_init(t_table *table);
//parse_nput.c
void	input_parse(t_table *table, char **av);
//getters_setters.c
void	set_b(t_mtx *mutex, bool *dest, bool value);
bool	get_b(t_mtx *mutex, bool *value);
void	set_l(t_mtx *mutex, long *dest, long value);
long	get_l(t_mtx *mutex, long *value);
bool	end_sim(t_table *table);
//synchro_utils.c
void	wait_all_threads(t_table *table);
//write.c
void	write_status(t_philo_status status, t_philo *philo);
//monitor.c
void	*monitor_dinner(void *table);
//dinner.c
void	dinner_start(t_table *table);
#endif
