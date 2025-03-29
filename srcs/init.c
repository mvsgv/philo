/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:24 by mavissar          #+#    #+#             */
/*   Updated: 2025/03/29 18:15:58 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	init_philos(t_table *table)
{
	long	i;

	i = table->nbr_philos;
	while (--i >= 0)
	{
		table->philo[i].id = i + 1;
		table->philo[i].eating = 0;
		table->philo[i].meals_eaten = 0;
		table->philo[i].is_dead = 0;
		table->philo[i].last_meals_time = current_time();
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork = &table->forks[(i + 1) % table->nbr_philos];
		table->philo[i].table = table;
	}
}

static void	init_forks(t_table *table)
{
	int	i;

	i = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nbr_philos);
	if (!table->forks)
		error_msg("Failed malloc for forks");
	while (++i < table->nbr_philos)
		pthread_mutex_init(&table->forks[i], NULL);
}

static void	*init_table(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		error_msg("Memory allocation failed for table");
	table->is_dead = 0;
	table->simulation_stop = false;
	table->begining = current_time();
	table->nbr_philos = ft_atol(argv[1]);
	table->time_die = ft_atol(argv[2]);
	table->time_eat = ft_atol(argv[3]);
	table->time_sleep = ft_atol(argv[4]);
	if (table->time_die < 60 || table->time_eat < 60 || table->time_sleep < 60
		|| table->nbr_philos <= 0)
		error_msg("Error: Invalid input.");
	if (argv[5])
		table->nb_meals = ft_atol(argv[5]);
	else
		table->nb_meals = -1;
	return (table);
}

t_table	*init_param(char **argv)
{
	int		i;
	t_table	*table;

	i = -1;
	table = init_table(argv);
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->check_mutex, NULL);
	table->philo = malloc(sizeof(t_philo) * table->nbr_philos);
	if (!table->philo)
		error_msg("Error: Failed malloc for philo\n");
	init_forks(table);
	while (++i < table->nbr_philos)
		table->philo[i].table = table;
	return (table);
}
