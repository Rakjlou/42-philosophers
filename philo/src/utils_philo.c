/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:38:33 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 22:51:24 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include <unistd.h>

void	philo_wait(long value)
{
	unsigned long	start;
	unsigned long	now;

	start = mstimestamp();
	while (42)
	{
		usleep(100);
		now = mstimestamp();
		if (now - start >= (unsigned long)value)
			break ;
	}
}

unsigned long	get_last_meal(t_philosopher *philo)
{
	unsigned long	result;

	pthread_mutex_lock(&philo->meal);
	result = philo->last_meal;
	pthread_mutex_unlock(&philo->meal);
	return (result);
}

void	set_last_meal(t_philosopher *philo, unsigned long value)
{
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = value;
	pthread_mutex_unlock(&philo->meal);
}

unsigned int	get_ate(t_philosopher *philo)
{
	unsigned int	result;

	pthread_mutex_lock(&philo->ate_mutex);
	result = philo->ate;
	pthread_mutex_unlock(&philo->ate_mutex);
	return (result);
}

void	incr_ate(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->ate_mutex);
	++philo->ate;
	pthread_mutex_unlock(&philo->ate_mutex);
}
