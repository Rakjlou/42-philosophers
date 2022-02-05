/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 20:10:33 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/05 00:09:07 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdio.h>
#include <sys/time.h>

void	log_action(t_philosopher *philo, const char *msg)
{
	t_game			*game;
	unsigned long	now;

	if (!game_continues(philo))
		return ;
	game = (t_game *)philo->game;
	now = mstimestamp();
	printf("%lu %u %s\n", now - game->start, philo->name, msg);
}

unsigned long	ms_since_last_meal(t_philosopher *philo)
{
	return (mstimestamp() - get_last_meal(philo));
}

unsigned long	mstimestamp(void)
{
	t_time	now;

	if (gettimeofday(&now, NULL) != 0)
		return (0);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

int	game_continues(t_philosopher *philo)
{
	int		result;
	t_game	*game;

	game = (t_game *)philo->game;
	pthread_mutex_lock(&game->lock);
	result = game->continues;
	pthread_mutex_unlock(&game->lock);
	return (result);
}

void	game_stop(t_game *game)
{
	pthread_mutex_lock(&game->lock);
	game->continues = 0;
	pthread_mutex_unlock(&game->lock);
}
