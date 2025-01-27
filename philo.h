/*Use struct if:

	You prefer clarity and explicitly want to include struct in your declarations.
	You don’t mind the extra verbosity.
	When you declare a struct,
		you must always use the keyword struct when referencing it.

Use typedef struct if:

	You want cleaner, shorter, and more modern-looking code.
	You’re working in large projects where you'll reference the struct often.
	Using typedef struct lets you create an alias(a shorthand) for the struct_t.
	This means you can refer to the struct without needing the struct keyword.*/

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>   // INT_MAX
# include <pthread.h>  // mutexes, threads
# include <stdbool.h>  // bool
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <sys/time.h> // gettimeofday
# include <unistd.h>   //write, usleep

# ifndef COLORS_H
#  define COLORS_H

// Reset
#  define RST "\033[0m"

// Bold Foreground Colors
#  define BLACK "\033[1;30m"
#  define RED "\033[1;31m"
#  define GREEN "\033[1;32m"
#  define YELLOW "\033[1;33m"
#  define BLUE "\033[1;34m"
#  define MAGENTA "\033[1;35m"
#  define CYAN "\033[1;36m"
#  define WHITE "\033[1;37m"

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

typedef struct s_philo
{
	int					id;
	long				meals_count;
	bool				full;
	long 				last_meal_time; // time passed from last meal intake
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t 			thread_id; // eahc philo is a thread
	t_table				*table;
}						t_philo;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

/*   ./philo       5           800             200            200      [5]*/
/*     prog     nb_philo    time_to_die    time_to_eat  time_to_sleep x_eat*/

typedef struct s_table
{
	long				nbr_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				x_time_meals;
	long 				start_simulation; // time
	long 				end_simulation; //triggered if philo died/have eaten
	t_fork 				*forks;	// array of forks at the table
	t_philo 			*philos; // array of philos at the table
}						t_table;

/* ************************************************************************** */
/*                                	CODE									  */
/* ************************************************************************** */
void					exit_error(const char *error);

#endif