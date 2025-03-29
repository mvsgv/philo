/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:56:05 by mavissar          #+#    #+#             */
/*   Updated: 2025/03/29 15:38:25 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef COLORS_H
#  define COLORS_H

// Reset
#  define RST "\033[0m"

// Bold Foreground Colors
#  define BLACK "\033[1;30m"
#  define RED "\033[1;31m"
#  define GREEN "\033[1;32m"
#  define Y "\033[1;33m"
#  define BLUE "\033[1;34m"
#  define MA "\033[1;35m"
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

typedef struct s_philo
{
	long			id;
	long			eating;
	long			meals_eaten;
	long			last_meals_time;
	pthread_t		thread;
	pthread_t		meal_print;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_table	*table;
	bool			*simulation_stop;
	long			is_dead;

}					t_philo;

typedef struct s_table
{
	long			nbr_philos;
	long			time_eat;
	long			time_die;
	long			time_sleep;
	long			nb_meals;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	check_mutex;
	long			is_dead;
	bool			simulation_stop;
	t_philo			*philo;

}					t_table;

void				error_msg(char *error);
t_table				*init_param(char **argv);
void				init_philos(t_table *table);
void				my_usleep(long time_sleep);
void				print_action(t_philo *philo, char *action);
void				eat(t_philo *philo);
void				*routine(void *arg);
void				find_fork(t_philo *philo,
						pthread_mutex_t **ff, pthread_mutex_t **sf);
char				*ft_strstr(const char *str, const char *find);
void				start_dinner(t_table *table);
long				current_time(void);
long				ft_atol(const char *str);
bool				is_philo_dead(t_philo *philo);
void				clean_up(t_table *data);

#endif