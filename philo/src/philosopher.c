/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:51:54 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/05 00:09:33 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static void	philo_sleep(t_philosopher *philo)
{
	t_game	*game;

	game = (t_game *)philo->game;
	log_action(philo, SLEEPING_MSG);
	philo_wait(game->rules.time_to_sleep);
}

static void	do_eat(t_philosopher *philo)
{
	t_game	*game;

	game = (t_game *)philo->game;
	log_action(philo, EATING_MSG);
	set_eating(philo, 1);
	philo_wait(game->rules.time_to_eat);
	set_eating(philo, 0);
	set_last_meal(philo, mstimestamp());
}

static void	philo_eat(t_philosopher *philo)
{
	get_forks(philo);
	do_eat(philo);
	pthread_mutex_unlock(&philo->lfork->lock);
	pthread_mutex_unlock(&philo->rfork->lock);
}

void	*philosopher(void *raw_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)raw_philo;
	while (game_continues(philo))
	{
		philo_eat(philo);
		if (game_continues(philo))
			philo_sleep(philo);
		else if (game_continues(philo))
			log_action(philo, THINKING_MSG);
	}
	return (NULL);
}
