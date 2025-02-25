/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:16:24 by mavissar          #+#    #+#             */
/*   Updated: 2025/02/25 17:19:33 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//The correct input must be ./philo 5 800 200 200  
//
//
//

#include "../inc/philo.h"

void	ft_exit_error(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}
static inline bool	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static inline bool is_space(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
//check for neg numb and legit nb
static const char *valid_input(const char *str)
{
	int	len;
	int i;
	const char *nb;

	len = 0;
	i = 0;
	while(is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		ft_exit_error("Only positive number accepted");
	if (!is_digit(*str))
		ft_exit_error("Wrong input! Only digits accepted");
	nb = str;
	while(is_digit(*str++))
		len++;
	if (len > 10)
		ft_exit_error("Wrong value! Maximum value is int max");
	return (nb);
}
static long ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		ft_exit_error("INT_MAX is the limit\n");
	return (num);
}
void	parsing(t_table *table, char **av)
{
	table->nbr_philo = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3; //scientific notationfor 1 w 3 0
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->time_to_die < 6e3 || table->time_to_eat < 6e3 
		||	table->time_to_sleep < 6e3)
			ft_exit_error("Use timestamps more than 60ms");
	if (av[5])
		table->x_time_meals = ft_atol(av[5]);
	else
		table->x_time_meals = -1;
}
