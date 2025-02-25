/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:33:47 by mavissar          #+#    #+#             */
/*   Updated: 2025/02/25 16:19:52 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	write_debug(t_philo_status status, t_philo *philo, long tl)
{
	if ((TAKE_FIRST_FORK == status)&& !simulation_finished(philo->table))
		printf(M"%-6ld"RST" %d has taken the first fork"
		"\t\t\tn˚"B"[🍴 %d 🍴]\n"RST, tl, philo->id,
				philo->first_fork->fork_id);
	if ((TAKE_SECOND_FORK == status)&& !simulation_finished(philo->table))
		printf(M"%-6ld"RST" %d has taken the second fork"
		"\t\t\tn˚"B"[🍴 %d 🍴]\n"RST, tl, philo->id,
				philo->second_fork->fork_id);
	else if ((EATING == status) && !simulation_finished(philo->table))
		printf(M"%-6ld"RST" %d has started eating\n"
		"\t\t\t"G"[🍦 %ld 🍦]\n"RST ,tl ,philo->id, philo->meals_count);
	else if ((SLEEPING == status) && !simulation_finished(philo->table))
		printf(M"%-6ld"RST" %d has started sleeping	💤\n", tl, philo->id);
	else if ((THINKING == status) && !simulation_finished(philo->table))
		printf(M"%-6ld"RST" %d started thinking 💭\n", tl, philo->id);
	else if ((DIED == status))
		printf(R"\t\t☠️ %-6ld %d died ☠️\n"RST ,tl ,philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	time_left;

	time_left = gettime(MILISECOND) - philo->table->start_simulation;
	safe_mutex(&philo->table->write_mutex, LOCK);
	if (philo->full)
		return ;
	if (debug)
		write_debug(status, philo, time_left);
	else 
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d has taken a fork\n", time_left, philo->id);
		else if ((EATING == status) && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d has started eating\n",time_left, philo->id);
		else if ((SLEEPING == status) && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d has started sleeping", time_left, philo->id);
		else if ((THINKING == status) && !simulation_finished(philo->table))
			printf(W"%-6ld"RST" %d started thinking\n", time_left, philo->id);
		else if ((DIED == status))
			printf(R"%-6ld"RST" %d died\n", time_left, philo->id);
	}
	safe_mutex(&philo->table->write_mutex, UNLOCK);

}