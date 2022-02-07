/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:30:05 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 21:12:24 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <sys/time.h>
#include <stdio.h>

void	*supervisor(void *raw_game)
{
	t_game			*game;
	t_philosopher	*philo;
	unsigned long	since_last_meal;
	unsigned long	time_to_die;
	long			i;

	game = (t_game *)raw_game;
	time_to_die = (unsigned long)game->rules.time_to_die;
	while (game_continues(&game->philos[0]))
	{
		i = 0;
		while (game_continues(&game->philos[0]) && i < game->rules.count)
		{
			philo = &game->philos[i];
			since_last_meal = ms_since_last_meal(philo);
			if (since_last_meal > time_to_die)
			{
				game_stop(game);
				printf("%lu %u %s\n", mstimestamp() - game->start, philo->name, DEATH_MSG);
				printf("%lu / %lu\n", since_last_meal, time_to_die);
			}
			++i;
		}
	}
	return (NULL);
}
