/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:11:26 by mavissar          #+#    #+#             */
/*   Updated: 2025/03/29 18:11:56 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	current_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	my_usleep(long time_sleep)
{
	long	strt;

	strt = current_time();
	while ((current_time() - strt) < time_sleep)
		usleep(100);
}
