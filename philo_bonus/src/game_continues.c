/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_continues.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 21:26:37 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 23:09:41 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <stdio.h>

int	game_continues(t_game *game)
{
	if (sem_wait(game->continues) == 0 && sem_post(game->continues) == 0)
		return (1);
	return (0);
}
