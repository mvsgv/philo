/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavissar <mavissar@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:33:01 by mavissar          #+#    #+#             */
/*   Updated: 2025/01/27 20:10:57 by mavissar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    if (argc == 5 || argc == 6)
    {

    }
    else 
    {
        exit_error(MAGENTA"Wrong input!"BG_WHITE
        "Correct :./philo 5 800 200 200\n"RST)
    }
}