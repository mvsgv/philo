/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:08:50 by mavissar          #+#    #+#             */
/*   Updated: 2025/02/18 22:42:13 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
static void	eat(t_philo *philo)
{
	safe_mutex(&philo->first_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MD);
	safe_mutex(&philo->first_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MD);
	set_long(&philo->philo_mtx, &philo->last_meal_time, gettime(MILISECOND));
	philo->meals_count++;
	write_status(EATING, philo, DEBUG_MD);
	my_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->x_time_meals > 0 
		&& philo->meals_count == philo->table->x_time_meals);
		set_bool(&philo->philo_mtx, &philo->full, true);
	safe_mutex(&philo->first_fork->fork, UNLOCK);
	safe_mutex(&philo->second_fork->fork, UNLOCK);
}
void	*dinner_simulation(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	//spinlock
	wait_all_threads(philo->table);
	
	while(!simulation_finished(philo->table))
	{
		// is phio full ?checl
		if (philo->full)
			break;
		//eat
 
		write_status(SLEEPING, philo, DEBUG_MD);
		my_usleep(philo->table->time_to_sleep, philo->table);
		//think
	}
}

void	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	if (0 == table->x_time_meals)
		return ; // back to main
	else if (1 == table->nbr_philo)
		return ;
	else 
	{
		while(i < table->nbr_philo)
			safe_thread(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	table->start_simulation = gettime(MILISECOND);
	set_bool(&t_table->table_mutex, &table->all_threads_ready, true);
	i = -1;
	while (++i < table->nbr_philo)
		safe_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
		
}