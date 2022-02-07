/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:01:23 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/08 00:34:14 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int	start_philos_step(t_game *game, long start)
{
	t_philosopher	*philo;
	long			i;

	i = start;
	while (i < game->rules.count)
	{
		philo = &game->philos[i];
		philo->last_meal = game->start;
		if (pthread_create(
				&philo->thread,
				NULL,
				philosopher,
				(void *)&game->philos[i]) != 0)
		{
			printf("Couldn't create thread %ld\n", i + 1);
			game_stop(game);
			while (--i >= 0)
				pthread_join(game->philos[i].thread, NULL);
			return (0);
		}
		i += 2;
		usleep(100);
	}
	return (1);
}

static int	start_philos(t_game *game)
{
	start_philos_step(game, 0);
	usleep(500);
	start_philos_step(game, 1);
	return (1);
}

static int	start_supervisor(t_game *game)
{
	if (pthread_create(
			&game->supervisor,
			NULL,
			supervisor,
			game) != 0)
	{
		printf("Couldn't create supervisor thread\n");
		game_stop(game);
		return (0);
	}
	return (1);
}

void	game_start(t_game *game)
{
	long	i;

	if (!start_philos(game))
		return ;
	else if (start_supervisor(game))
		pthread_join(game->supervisor, NULL);
	i = 0;
	while (i < game->rules.count)
		pthread_join(game->philos[i++].thread, NULL);
}
