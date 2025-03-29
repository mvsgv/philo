/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:45:41 by mavissar          #+#    #+#             */
/*   Updated: 2025/03/29 15:47:06 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	error_msg(char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void	clean_up(t_table *table)
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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->table->simulation_stop)
	{
		print_action(philo, BLUE "is thinking ( ꩜ ᯅ ꩜;) ? 𖡎" RST);
		if (philo->table->simulation_stop || philo->table->nbr_philos == 1)
			break ;
		eat(philo);
		if (philo->table->simulation_stop)
			break ;
		print_action(philo, Y "is sleeping _( _ _)__...zzZ ✩₊˚.⋆☾⋆⁺₊✧" RST);
		my_usleep(philo->table->time_sleep);
	}
	return (NULL);
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
