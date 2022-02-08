/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:38:11 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 23:40:50 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <sys/time.h>
# include <semaphore.h>
# include <unistd.h>
# include <pthread.h>

# define FORK_MSG "has taken a fork"
# define EATING_MSG "\033[0;32mis eating\033[0m"
# define SLEEPING_MSG "is sleeping"
# define THINKING_MSG "is thinking"
# define DEATH_MSG "\033[1;31mdied\033[0m"

typedef struct timeval	t_time;

typedef struct s_rules
{
	unsigned int	count;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	min_eat;
}	t_rules;

typedef struct s_philosopher
{
	unsigned int	dead;
	unsigned int	name;
	unsigned int	last_meal;
	pthread_t		thread;
	long			pid;
	void			*game;
}	t_philosopher;

typedef struct s_game
{
	t_rules			rules;
	sem_t			*forks;
	sem_t			*continues;
	t_philosopher	*philo;
	unsigned int	start;
}	t_game;

void			log_action(t_game *g, t_philosopher *philo, const char *action);
void			philo_wait(unsigned int value);
unsigned int	time_since_last_meal(t_philosopher *philo);
unsigned int	timestamp(void);

int				set_rules(t_game *game, int ac, char **av);
int				game_continues(t_game *game);
int				game_init(t_game *game);
void			game_start(t_game *game);
void			game_destroy(t_game *game);

void			philosopher(t_game *game, t_philosopher *philo);

#endif
