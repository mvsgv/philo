#include "philo.h"

void    init_philos(t_table *table)
{
    int i;

    i = 0;
    table->philo = malloc(sizeof(t_philo) * table->nbr_philos);
    if (!table->philo)
        error_msg("Memory allocation failed for philos");
    while (i++ < table->nbr_philos)
    {
        table->philo[i].id = i + 1;
        table->philo[i].meals_eaten = 0;
        table->philo[i].last_meals_time = 0;
        table->philo[i].left_fork = &table->forks[i];
        table->philo[i].right_fork = &table->forks[(i + 1) % table->nbr_philos];
    }
}

void    init_forks(t_table *table)
{
    int i;

    i = 0;
    table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
    if (!table->forks)
        error_msg("Failed malloc for forks");
    while (i < table->nbr_philos)
        pthread_mutex_init(&table->forks[i], NULL);

}

int main(int argc, char**argv)
{
    t_table *table;
    if (argc == 5 || argc == 6)
    {
        parsing(&table, argv);
        //init
        //start dinner
        //clean
    }
    else 
    {
        error_msg("Wrong number of arguments."
        " correct input : ./philo 5 800 200 200");
    }
}