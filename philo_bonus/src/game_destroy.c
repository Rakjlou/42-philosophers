/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:28:52 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 23:40:40 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void	game_destroy(t_game *game)
{
	int				exit_val;
	unsigned int	i;

	while (waitpid(-1, &exit_val, 0) > 0)
	{
		if (WIFEXITED(exit_val) && WEXITSTATUS(exit_val) == 42)
		{
			i = 0;
			while (i < game->rules.count)
			{
				printf("<<<<<<<<<<<%d %ld\n", i, game->philo[i].pid);
				kill(game->philo[i].pid, SIGTERM);
				++i;
			}
			break ;
		}
		puts("lksfjds");
	}
		puts("AAAAAAAAAAAAAAAAAAAA");
	sem_close(game->forks);
	sem_close(game->continues);
	free(game->philo);
}
