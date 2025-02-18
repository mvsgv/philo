/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:16:01 by mavissar          #+#    #+#             */
/*   Updated: 2025/02/18 22:09:17 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*what is a spinlock?*/
/*what is enum / why do we use it */
/*while all the threads are not ready you wait */
/*explain timeval usec, sec and 1e6 1e3 etc*/
/*spinlock to synchromiwe philo start*/
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, table->all_threads_ready)) // this is a spinlock
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

void	my_usleep(long usec, t_table *table)
{
	long	start;
	long	time_left;
	long	time_passed;
	
	start = gettime(MICROSECOND);
	while(gettime(MICROSECOND)- start < usec) // you sleep until i reacha certain level
	{
		if (simulation_finished(table))
			break;
		time_passed = gettime(MICROSECOND) - start;
		time_left = usec - time_passed;
		if(time_passed > 1e3) // if you reached this level you stop sleeping
			usleep(time_left / 2);
		else
		{
			while (gettime(MICROSECOND)- start < usec)
			;
		}	
	}
}
