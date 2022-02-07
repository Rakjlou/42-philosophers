/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 22:53:36 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 20:59:04 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdlib.h>
#include <stdio.h>

static int	malloc_forks_and_philos(t_game *game)
{
	game->philos = malloc(sizeof(t_philosopher) * game->rules.count);
	if (game->philos == NULL)
		return (printf("Failed creating philosophers\n"), 0);
	game->forks = malloc(sizeof(t_fork) * game->rules.count);
	if (game->forks == NULL)
		return (free(game->philos), printf("Failed creating forks\n"), 0);
	return (1);
}

static int	init_mutexes(t_game *game)
{
	long	i;

	i = 0;
	if (pthread_mutex_init(&game->lock, NULL) != 0)
		return (printf("Couldn't game mutex\n"), 0);
	while (i < game->rules.count)
	{
		if (pthread_mutex_init(&game->forks[i].lock, NULL) != 0)
			return (printf("Couldn't create fork mutexes\n"), 0);
		++i;
	}
	return (1);
}

static int	init_philos(t_game *game)
{
	long			i;
	t_philosopher	*philo;

	i = 0;
	while (i < game->rules.count)
	{
		philo = &game->philos[i];
		philo->name = i + 1;
		philo->ate = 0;
		philo->last_meal = 0;
		philo->game = (void *)game;
		if (pthread_mutex_init(&philo->meal, NULL) != 0)
			return (printf("Couldn't create eating mutex\n"), 0);
		game->forks[i].index = i;
		++i;
	}
	return (1);
}

static int	dispatch_forks(t_game *game)
{
	long	i;

	i = 0;
	while (i < game->rules.count)
	{
		game->philos[i].lfork = &game->forks[i];
		if (i == 0)
			game->philos[i].rfork = &game->forks[game->rules.count - 1];
		else
			game->philos[i].rfork = &game->forks[i - 1];
		++i;
	}
	return (1);
}

int	game_init(t_game *game)
{
	game->philos = NULL;
	game->forks = NULL;
	if (malloc_forks_and_philos(game)
		&& init_mutexes(game)
		&& init_philos(game)
		&& dispatch_forks(game))
	{
		game->continues = 1;
		game->start = mstimestamp();
		return (1);
	}
	return (0);
}
