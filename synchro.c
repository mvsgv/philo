/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:16:01 by mavissar          #+#    #+#             */
/*   Updated: 2025/02/06 17:53:39 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*what is a spinlock?*/
/*what is enum / why do we use it */
/*while all the threads are not ready you wait */
/*explain timeval usec, sec and 1e6 1e3 etc*/
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, table->all_threads_ready))
	; 
}
long	gettime(t_time_code time_code)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL))
		exit_error("Gettimeofday failed");
	else if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILISECOND== time_code)
		return ((tv.tv_sec * 1e3 )+ (tv.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		exit_error("Wron gettime input");
	return (42);
}