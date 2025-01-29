/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:16:24 by mavissar          #+#    #+#             */
/*   Updated: 2025/01/27 20:09:10 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//The correct input must be ./philo 5 800 200 200  
//
//
//

#include "philo.h"

void	exit_erro(const char *error)
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
static long atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - 48);
	if (num > INT_MAX)
		exit_error("INT_MAX is the limit\n");
	return (num);
}
static const char valid_input(const char *str)
{
	int	len;
	const char *nb;

	len = 0;
	while(is_space(*str))
		*str++;
	if (*str == '+')
		*str++;
	else if (*str == '-')
		exit_error("Only positive number accepted");
	if (!is_digit(*str))
		exit_error("Wrong input! Only digits accepted");
	nb = str;
	while(is_digit(*str++))
		len++;
	if (len > 10)
		exit_error("Wrong value! Maximum value is int max");
	return (nb);
}
