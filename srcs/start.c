/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:08:50 by mavissar          #+#    #+#             */
/*   Updated: 2025/02/25 17:24:50 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MD);
}

static void	eat(t_philo *philo)
{
	// 1 LOCK
	safe_mutex(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MD);
	safe_mutex(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MD);
	// 2 EAT
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILISECOND));
	philo->meals_count++;
	write_status(EATING, philo, DEBUG_MD);
	my_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->x_time_meals > 0 
		&& philo->meals_count == philo->table->x_time_meals)
		set_bool(&philo->philo_mtx, &philo->full, true);
	// 3 UNLOCK
	safe_mutex(&philo->first_fork->fork, UNLOCK);
	safe_mutex(&philo->second_fork->fork, UNLOCK);
}
void	*dinner_simulation(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	//spinlock
	wait_all_threads(philo->table);
	increase_long(&philo->table->table_mutex,
					&philo->table->nbr_threads_running);
	while(!simulation_finished(philo->table))
	{
		if (philo->full)
			break;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MD);
		my_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}

void	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	if (0 == table->x_time_meals)
		return ; // back to main
	else if (1 == table->nbr_philo)
		return ;
	while(i < table->nbr_philo)
		safe_thread(&table->philos[i].thread_id, dinner_simulation,
			&table->philos[i], CREATE);
	safe_thread(&table->monitor, dinner_monitor, table, CREATE);
	table->start_simulation = gettime(MILISECOND);
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	i = 0;
	while (i < table->nbr_philo)
	{
		safe_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}

// static bool	philo_died(t_philo *philo)
// {
// 	write_status(DIED, philo, DEBUG_MD);
// }

void	*dinner_monitor(void *data)
{
	t_table *table;
	int		i;

	table = (t_table *)data;
	while(!all_threads_running(&table->table_mutex, &table->nbr_threads_running, 
				table->nbr_philo))
				;
	while(!simulation_finished(table))
	{
		i = 0;
		while (i < table->nbr_philo && !simulation_finished(table))
		{
			// if (philo_died(table->philos + i))
			// {
			// 	set_bool(&table->table_mutex, &table->end_simulation, true);
			// 	write_status(DIED, table->philos + i, DEBUG_MD);
			// }
			i++;
		}
	}
	return (NULL);
}