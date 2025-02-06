/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:17:50 by mavissar          #+#    #+#             */
/*   Updated: 2025/02/06 16:46:56 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assignation_of_forks(t_philo *philo, t_fork *forks, int philo_pos)
{
	int	philo_nbr;

	philo_nbr = philo->table->nbr_philo;

	philo->first_fork = &forks[(philo_pos + 1) % philo_nbr];
	philo->second_fork = &forks[philo_pos];
	if (philo->id % 2)
	{
		philo->first_fork = &forks[philo_pos];
		philo->second_fork = &forks[(philo_pos + 1) % philo_nbr];
	}
}

static void	philos_init(t_table *table)
{
	int		i;
	t_philo *philos;
	
	i = 0;
	while (i < table->nbr_philo)
	{
		philos = table->philos + i;
		philos->id = i + 1;
		philos->full = false;
		philos->meals_count = 0;
		philos->table = table;

		assignation_of_forks(philos, table->forks, i);
	}
}
void	data_init(t_table *table)
{
	int	i;
	
	i = 0;
	table->end_simulation = false;
	table->all_threads_ready = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->nbr_philo);
	safe_mutex(&table->table_mutex, INIT);
	table->forks = safe_malloc(sizeof(t_fork) * table->nbr_philo);
	while (i < table->nbr_philo)
	{
		safe_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = 1; //each fork has a num
	}
	philos_init(table)
}
