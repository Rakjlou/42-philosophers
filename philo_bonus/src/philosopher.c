/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:09:43 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 23:34:51 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdlib.h>
#include <stdio.h>

static void	pick_fork(t_game *game, t_philosopher *philo)
{
	if (sem_wait(game->forks) == 0)
		log_action(game, philo, FORK_MSG);
	else
	{
		printf("Pick fork error\n");
		exit(EXIT_FAILURE);
	}
}

static int	eat(t_game *game, t_philosopher *philo)
{
	if (game->rules.count == 1)
		return (0);
	pick_fork(game, philo);
	pick_fork(game, philo);
	if (game_continues(game))
	{
		philo->last_meal = timestamp();
		log_action(game, philo, EATING_MSG);
		philo_wait(game->rules.time_to_eat);
		sem_post(game->forks);
		sem_post(game->forks);
		return (1);
	}
	else
		return (0);
}

static void	phsleep(t_game *game, t_philosopher *philo)
{
	if (!game_continues(game))
		return ;
	log_action(game, philo, SLEEPING_MSG);
	philo_wait(game->rules.time_to_sleep);
}

static void	*supervisor(void *philo_raw)
{
	t_philosopher	*philo;
	t_game			*game;

	philo = philo_raw;
	game = philo->game;
	while (game_continues((t_game *)philo->game))
	{
		if (time_since_last_meal(philo) > game->rules.time_to_die)
		{
			log_action(game, philo, DEATH_MSG);
			sem_wait(game->continues);
			exit(42);
			return (NULL);
		}
		philo_wait(1);
	}
	return (NULL);
}

void	philosopher(t_game *game, t_philosopher *philo)
{
	philo->game = game;
	if (pthread_create(&philo->thread, NULL, supervisor, philo) != 0)
		(printf("Thread error %u\n", philo->name), exit(EXIT_FAILURE));
	while (game_continues(game))
	{
		if (eat(game, philo))
		{
			phsleep(game, philo);
			log_action(game, philo, THINKING_MSG);
		}
	}
	pthread_join(philo->thread, NULL);
	exit(EXIT_SUCCESS);
}
