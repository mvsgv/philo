/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:54:21 by mavissar          #+#    #+#             */
/*   Updated: 2025/02/25 16:04:44 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>   // INT_MAX
# include <pthread.h>  // mutexes, threads
# include <stdbool.h> // bool
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <sys/time.h> // gettimeofday
# include <unistd.h>   //write, usleep
# include <errno.h> // to handle errors

# ifndef COLORS_H
#  define COLORS_H

# define DEBUG_MD 0
// Reset
#  define RST "\033[0m"

// Bold Foreground Colors
#  define B "\033[1;30m"
#  define R "\033[1;31m"
#  define G "\033[1;32m"
#  define YELLOW "\033[1;33m"
#  define M "\033[1;35m"
#  define CYAN "\033[1;36m"
#  define W "\033[1;37m"

// Bold Background Colors
#  define BG_BOLD_BLACK "\033[1;40m"
#  define BG_BOLD_RED "\033[1;41m"
#  define BG_BOLD_GREEN "\033[1;42m"
#  define BG_BOLD_YELLOW "\033[1;43m"
#  define BG_BOLD_BLUE "\033[1;44m"
#  define BG_BOLD_MAGENTA "\033[1;45m"
#  define BG_BOLD_CYAN "\033[1;46m"
#  define BG_WHITE "\033[1;47m"

# endif // COLORS_H

/* ************************************************************************** */
/*                                  STRUCTURES				                  */
/* ************************************************************************** */


typedef pthread_mutex_t	t_mtx;
typedef struct s_table t_table;  // forward declaration


typedef enum e_opcode {
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
} 			t_philo_status;

typedef enum e_time_code
{
	SECOND,
	MILISECOND,
	MICROSECOND,
} 			t_time_code;


typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

/*   ./philo       5           800             200            200      [5]*/
/*     prog     nb_philo    time_to_die    time_to_eat  time_to_sleep x_eat*/
typedef struct s_philo
{
	int					id;
	long				meals_count;
	bool				full;
	long 				last_meal_time; // time passed from last meal intake
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t 			thread_id; // eahc philo is a thread
	t_mtx				philo_mtx;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	long				nbr_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				x_time_meals;
	long 				start_simulation; // time
	bool				all_threads_ready;
	bool 				end_simulation; //triggered if philo died/have eaten
	t_mtx				table_mutex; //avoid races while reading from table
	t_mtx				write_mutex; //
	long				nbr_threads_running;
	pthread_t			monitor; 
	t_fork 				*forks;	// array of forks at the table
	t_philo 			*philos; // array of philos at the table
}						t_table;



/* ************************************************************************** */
/*                                	CODE									  */
/* ************************************************************************** */
/*utils*/
void	increase_long(t_mtx *mutex, long *value);
bool	all_threads_running(t_mtx *mutex, long *threads, long nbr_philo);
void	write_status(t_philo_status status, t_philo *philo, bool debug);
void	ft_exit_error(const char *error);
void	my_usleep(long usec, t_table *table);
/*safety functions*/
void	*safe_malloc(size_t bytes);
void	safe_mutex(t_mtx *mutex, t_opcode opcode);
void	safe_thread(pthread_t *thread, 
			void *(*foo)(void*), void *data, t_opcode opcode);
/*init*/
void	data_init(t_table *table);
/*getters_setters*/
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	simulation_finished(t_table *table);
/*synchro_utils*/
void	wait_all_threads(t_table *table);
long	gettime(t_time_code time_code);

void	parsing(t_table *table, char **av);

void	*dinner_simulation(void *data);
void	*dinner_monitor(void *data);
void	start_dinner(t_table *table);
#endif
