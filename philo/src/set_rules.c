/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rules.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:39:57 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 22:58:32 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "minilibft.h"
#include <stddef.h>

static int	rules_are_valid(int ac, char **av)
{
	if (ac == 5)
	{
		return (
			ft_isnum(av[1])
			&& ft_isnum(av[2])
			&& ft_isnum(av[3])
			&& ft_isnum(av[4])
		);
	}
	return (
		ft_isnum(av[1])
		&& ft_isnum(av[2])
		&& ft_isnum(av[3])
		&& ft_isnum(av[4])
		&& ft_isnum(av[5])
	);
}

int	set_rules(t_game *game, int ac, char **av)
{
	if (!rules_are_valid(ac, av))
		return (0);
	game->rules.count = ft_atol(av[1]);
	game->rules.time_to_die = ft_atol(av[2]);
	game->rules.time_to_eat = ft_atol(av[3]);
	game->rules.time_to_sleep = ft_atol(av[4]);
	game->rules.min_eat = 0;
	if (ac == 6)
	{
		game->rules.min_eat = ft_atol(av[5]);
		return (
			game->rules.count > 0
			&& game->rules.time_to_die > 0
			&& game->rules.time_to_eat > 0
			&& game->rules.time_to_sleep > 0
			&& game->rules.min_eat > 0
		);
	}
	return (
		game->rules.count > 0
		&& game->rules.time_to_die > 0
		&& game->rules.time_to_eat > 0
		&& game->rules.time_to_sleep > 0
	);
}
