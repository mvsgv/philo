/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:33:01 by mavissar          #+#    #+#             */
/*   Updated: 2025/02/25 17:15:25 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	t_table table;
	
	if (argc == 5 || argc == 6)
	{
		parsing(&table, argv);
		data_init(&table);
		start_dinner(&table);
		//clean(&table);
	}
	else 
	{
		ft_exit_error(M"Wrong input!"W
		"Correct :./philo 5 800 200 200\n"RST);
	}
}
