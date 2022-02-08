/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:30:38 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 22:19:09 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdio.h>
#include <unistd.h>

unsigned int	timestamp(void)
{
	t_time	now;

	if (gettimeofday(&now, NULL) != 0)
		return (0);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

unsigned int	time_since_last_meal(t_philosopher *philo)
{
	unsigned int	now;

	now = timestamp();
	return (now - philo->last_meal);
}

void	log_action(t_game *game, t_philosopher *philo, const char *action)
{
	unsigned int	now;

	if (!game_continues(game))
		return ;
	now = timestamp();
	printf("%u %u %s\n", now - game->start, philo->name, action);
}

void	philo_wait(unsigned int value)
{
	unsigned int	start;
	unsigned int	now;

	start = timestamp();
	while (42)
	{
		usleep(100);
		now = timestamp();
		if (now - start >= value)
			break ;
	}
}
