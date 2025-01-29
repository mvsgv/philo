/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:33:01 by mavissar          #+#    #+#             */
/*   Updated: 2025/01/29 17:20:30 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		// check_correct_input 
		// parsing;
		// data_init
		// start_dinner
		// leaks_check
	}
	else 
	{
		exit_error(MAGENTA"Wrong input!"BG_WHITE
		"Correct :./philo 5 800 200 200\n"RST)
	}
}
