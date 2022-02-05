/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:38:33 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/05 00:07:29 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <unistd.h>

unsigned int	is_eating(t_philosopher *philo)
{
	unsigned int		result;

	pthread_mutex_lock(&philo->eating);
	result = philo->is_eating;
	pthread_mutex_unlock(&philo->eating);
	return (result);
}

unsigned int	is_sleeping(t_philosopher *philo)
{
	unsigned int	result;

	pthread_mutex_lock(&philo->eating);
	result = philo->is_sleeping;
	pthread_mutex_unlock(&philo->eating);
	return (result);
}

void	set_eating(t_philosopher *philo, unsigned int value)
{
	pthread_mutex_lock(&philo->eating);
	philo->is_eating = value;
	pthread_mutex_unlock(&philo->eating);
}

void	set_sleeping(t_philosopher *philo, unsigned int value)
{
	pthread_mutex_lock(&philo->eating);
	philo->is_sleeping = value;
	pthread_mutex_unlock(&philo->eating);
}

void	philo_wait(long value)
{
	usleep(value * 1000);
}
