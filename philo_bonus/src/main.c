/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 21:38:37 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/08 01:01:59 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "game.h"

static int	print_arg_error(void)
{
	printf(
		"%s\n%s\n%s\n",
		"Error",
		"All arguments must be positive numbers",
		"Or less likely, gettimeofday failed");
	return (EXIT_FAILURE);
}

static int	print_usage(void)
{
	printf(
		"Usage: ./philo %s %s %s %s [%s]\n",
		"number_of_philosophers",
		"time_to_die",
		"time_to_eat",
		"time_to_sleep",
		"number_of_times_each_philosopher_must_eat");
	return (EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac < 5 || ac > 6)
		return (print_usage());
	else if (!set_rules(&game, ac, av))
		return (print_arg_error());
	else if (!game_init(&game))
		return (game_destroy(&game), EXIT_FAILURE);
	game_start(&game);
	game_destroy(&game);
	return (EXIT_SUCCESS);
}
