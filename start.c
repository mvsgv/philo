/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:08:50 by mavissar          #+#    #+#             */
/*   Updated: 2025/02/06 17:57:49 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_simulation(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	
	wait_all_threads(philo->table);
	
}

void	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	if (0 == table->x_time_meals)
		return ;
	else if (1 == table->nbr_philo)
		return ;
	else 
	{
		while(i < table->nbr_philo)
			safe_thread(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	table->start_simulation = gettime(MILISECOND)
	set_bool(&t_table->table_mutex, &table->all_threads_ready, true);
}