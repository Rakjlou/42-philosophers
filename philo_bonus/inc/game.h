/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:38:11 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/08 00:58:25 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <sys/time.h>
# include <pthread.h>

# define FORK_MSG "has taken a fork"
# define EATING_MSG "\033[0;32mis eating\033[0m"
# define SLEEPING_MSG "is sleeping"
# define THINKING_MSG "is thinking"
# define DEATH_MSG "\033[1;31mdied\033[0m"

typedef struct timeval	t_time;

typedef struct s_rules
{
	long	count;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	min_eat;
}	t_rules;

typedef struct s_game
{
	t_rules			rules;
}	t_game;

int				set_rules(t_game *game, int ac, char **av);

int				game_init(t_game *game);
void			game_start(t_game *game);
void			game_destroy(t_game *game);

#endif
