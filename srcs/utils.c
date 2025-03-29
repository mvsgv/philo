/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:03:29 by mavissar          #+#    #+#             */
/*   Updated: 2025/03/29 15:25:20 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

char	*ft_strstr(const char *str, const char *find)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!find[i])
		return ((char *)str);
	while (str[i])
	{
		while (str[i + j] == find[j] && str[i + j] != '\0' && i + j && find[j])
			j++;
		if (find[j] == '\0')
			return ((char *)&str[i]);
		i++;
		j = 0;
	}
	return (0);
}

static long	valid_input_check(const char *str)
{
	long	index;
	long	len;
	char	nb;

	len = 0;
	index = 0;
	if (str[index] == ' ')
		index++;
	else if (str[index] == '+')
		index++;
	else if ((str[index] < '0' && str[index] > '9'))
		error_msg("Only gidits accepted");
	else if (str[index] == '-')
		error_msg("Only positive numbers accepted");
	nb = str[0];
	while ((str[index] < '0' && str[index] > '9'))
		len++;
	if (len > 10)
		error_msg("Error! INT MAX is the limit");
	return (nb);
}

long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	valid_input_check(str);
	while ((*str >= '0' && *str <= '9'))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		error_msg("INT MAX is the limit, please enter smaller numbers");
	return (num);
}

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
