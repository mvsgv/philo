#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <sys/time.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo{
    long    id; // philo id 
    long    meals_eaten; // nb of meals eaten
    long    last_meals_time; //timestamps for last meal time 
    pthread_t       thread;           // Thread for the philosopher
    pthread_mutex_t   *right_fork;
    pthread_mutex_t   *left_fork;    
    t_table *table;
}t_philo;

typedef struct s_table{
    long    nbr_philos;
    long    time_eat;
    long    time_die;
    long    time_sleep;
    long    nb_meals;
    pthread_mutex_t *forks;
    t_philo *philo;
} t_table;

//PARSING
void    error_msg(char *error);
void    parsing(int argc, char **argv);

#endif