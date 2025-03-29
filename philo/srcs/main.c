/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:45:41 by mavissar          #+#    #+#             */
/*   Updated: 2025/03/29 18:22:40 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	clean_up(t_table *table)
{
	int	i;

	table->simulation_stop = true;
	my_usleep(1000);
	i = -1;
	while (++i < table->nbr_philos)
		pthread_join(table->philo[i].thread, NULL);
	i = -1;
	while (++i < table->nbr_philos)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->check_mutex);
	free(table->philo);
	free(table->forks);
	free(table);
}

static void	start_dinner(t_table *table)
{
	pthread_t	monitor;
	int			i;

	i = -1;
	init_philos(table);
	table->simulation_stop = false;
	while (++i < table->nbr_philos)
		pthread_create(&table->philo[i].thread, NULL, routine,
			&table->philo[i]);
	pthread_create(&monitor, NULL, monitor_routine, table);
	pthread_join(monitor, NULL);
	table->simulation_stop = true;
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (argc == 5 || argc == 6)
	{
		table = init_param(argv);
		start_dinner(table);
		clean_up(table);
	}
	else
	{
		error_msg("Wrong number of arguments."
			" correct input : ./philo 5 800 200 200");
	}
}
