/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:30:05 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/05 01:10:10 by nsierra-         ###   ########.fr       */
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
			if (!is_eating(philo) && since_last_meal > time_to_die)
			{
				log_action(&game->philos[i], DEATH_MSG);
				printf("%lu / %lu\n", since_last_meal, time_to_die);
				game_stop(game);
			}
			++i;
		}
	}
	return (NULL);
}
