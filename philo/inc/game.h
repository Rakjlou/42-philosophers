/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 22:38:11 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 20:58:39 by nsierra-         ###   ########.fr       */
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

typedef struct s_fork
{
	int				index;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_philosopher
{
	unsigned int	name;
	unsigned int	ate;
	unsigned long	last_meal;
	pthread_mutex_t	meal;
	pthread_t		thread;
	t_fork			*lfork;
	t_fork			*rfork;
	void			*game;
}	t_philosopher;

typedef struct s_game
{
	int				continues;
	unsigned long	start;
	pthread_mutex_t	lock;
	pthread_t		supervisor;
	t_rules			rules;
	t_philosopher	*philos;
	t_fork			*forks;
}	t_game;

int				set_rules(t_game *game, int ac, char **av);

int				game_init(t_game *game);
void			game_start(t_game *game);
void			game_destroy(t_game *game);
int				game_continues(t_philosopher *philo);
void			game_stop(t_game *game);

void			*philosopher(void *raw_philo);
void			*supervisor(void *raw_game);

unsigned long	get_last_meal(t_philosopher *philo);
void			set_last_meal(t_philosopher *philo, unsigned long value);
void			philo_wait(long value);

void			get_forks(t_philosopher *philo);
void			release_forks(t_philosopher *philo);

void			log_action(t_philosopher *philo, const char *msg);
unsigned long	ms_since_last_meal(t_philosopher *philo);
unsigned long	mstimestamp(void);


#endif
