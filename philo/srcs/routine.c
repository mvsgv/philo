/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:08:34 by mavissar          #+#    #+#             */
/*   Updated: 2025/03/29 18:25:47 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	find_f(t_philo *philo, pthread_mutex_t **ff, pthread_mutex_t **sf)
{
	if (philo->id % 2 == 0)
	{
		*ff = philo->right_fork;
		*sf = philo->left_fork;
	}
	else
	{
		*ff = philo->left_fork;
		*sf = philo->right_fork;
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	find_f(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	print_action(philo, W "has taken first fork 𐂐" RST);
	pthread_mutex_lock(second_fork);
	print_action(philo, W "has taken second fork 𐂐" RST);
	pthread_mutex_lock(&philo->table->check_mutex);
	philo->eating = true;
	philo->last_meals_time = current_time();
	pthread_mutex_unlock(&philo->table->check_mutex);
	print_action(philo, GREEN "is eating ( ´ཀ` ) ‧₊˚ ⋅ 𓐐𓎩 ‧₊˚ ⋅" RST);
	my_usleep(philo->table->time_eat);
	pthread_mutex_lock(&philo->table->check_mutex);
	philo->meals_eaten++;
	philo->eating = false;
	pthread_mutex_unlock(&philo->table->check_mutex);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
}

static bool	philo_died(t_table *table, t_philo *philo)
{
	long	now;

	pthread_mutex_lock(&table->check_mutex);
	now = current_time();
	if ((now - philo->last_meals_time) > table->time_die && !philo->eating)
	{
		print_action(philo, RED "philo died ༼ ༎ຶ ෴ ༎ຶ༽ ﮩ٨ـﮩﮩ٨ـ♡ﮩ٨ـﮩﮩ٨ـ" RST);
		table->simulation_stop = true;
		table->is_dead = 1;
		pthread_mutex_unlock(&table->check_mutex);
		return (true);
	}
	pthread_mutex_unlock(&table->check_mutex);
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	long	i;

	table = (t_table *)arg;
	while (!table->simulation_stop)
	{
		i = -1;
		while (++i < table->nbr_philos)
			if (philo_died(table, &table->philo[i]))
				return (NULL);
		usleep(1000);
	}
	return (NULL);
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
