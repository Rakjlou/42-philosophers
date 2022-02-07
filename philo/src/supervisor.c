/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:30:05 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 22:33:07 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

static int	dying_end(t_philosopher *philo)
{
	unsigned long	since_last_meal;
	unsigned long	time_to_die;
	t_game			*game;

	game = (t_game *)philo->game;
	time_to_die = (unsigned long)game->rules.time_to_die;
	since_last_meal = ms_since_last_meal(philo);
	if (since_last_meal > time_to_die)
	{
		game_stop(game);
		printf(
			"%lu %u %s\n",
			mstimestamp() - game->start,
			philo->name,
			DEATH_MSG);
		printf("%lu / %lu\n", since_last_meal, time_to_die);
		return (1);
	}
	return (0);
}

static int	eating_end(t_game *game, long full)
{
	if (game->rules.min_eat > 0 && full >= game->rules.count)
	{
		game_stop(game);
		return (1);
	}
	return (0);
}

void	*supervisor(void *raw_game)
{
	t_game			*game;
	t_philosopher	*philo;
	long			full;
	long			i;

	game = (t_game *)raw_game;
	while (game_continues(&game->philos[0]))
	{
		i = 0;
		full = 0;
		while (game_continues(&game->philos[0]) && i < game->rules.count)
		{
			philo = &game->philos[i];
			if (dying_end(philo))
				return (NULL);
			else if (get_ate(philo) >= (unsigned int)game->rules.min_eat)
				++full;
			++i;
			usleep(50);
		}
		if (eating_end(game, full))
			return (NULL);
	}
	return (NULL);
}
