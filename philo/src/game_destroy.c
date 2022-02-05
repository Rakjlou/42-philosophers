/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:28:52 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/04 23:13:44 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdlib.h>

void	game_destroy(t_game *game)
{
	int	i;

	i = 0;
	free(game->philos);
	while (i < game->rules.count)
	{
		pthread_mutex_destroy(&game->forks[i].lock);
		++i;
	}
	free(game->forks);
}
