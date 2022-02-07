/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 00:06:21 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 20:58:17 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

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
