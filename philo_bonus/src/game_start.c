/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:01:23 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 23:41:41 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void	game_start(t_game *game)
{
	unsigned int	i;
	pid_t			pid;

	i = 0;
	game->start = timestamp();
	while (i < game->rules.count)
	{
		pid = fork();
		if (pid == -1)
		{
			printf("Fork error\n");
			break ;
		}
		else if (pid == 0)
		{
			game->philo[i].dead = 1;
			game->philo[i].name = i + 1;
			game->philo[i].last_meal = game->start;
			philosopher(game, game->philo + i);
		}
		else
		{
			game->philo[i].pid = (long)pid;
			printf("Child %d pid %ld\n", i, game->philo[i].pid);
		}
		++i;
	}
}
