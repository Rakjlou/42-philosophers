/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 22:53:36 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 23:09:53 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int	game_init(t_game *game)
{
	game->forks = sem_open(
			"/42-philos",
			O_CREAT,
			S_IRUSR | S_IWUSR,
			game->rules.count);
	if (game->forks == SEM_FAILED)
		return (0);
	sem_unlink("/42-philos");
	game->continues = sem_open(
			"/42-philos-continues",
			O_CREAT,
			S_IRUSR | S_IWUSR,
			1);
	if (game->continues == SEM_FAILED)
		return (sem_close(game->forks), 0);
	sem_unlink("/42-philos-continues");
	game->philo = malloc(sizeof(t_philosopher) * game->rules.count);
	if (game->philo == NULL)
		return (sem_close(game->forks), sem_close(game->continues), 0);
	return (1);
}
