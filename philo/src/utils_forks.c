/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:55:55 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 21:59:27 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	sort_forks(t_philosopher *philo, t_fork **first, t_fork **second)
{
	if (philo->rfork->index < philo->lfork->index)
	{
		*first = philo->rfork;
		*second = philo->lfork;
	}
	else
	{
		*first = philo->lfork;
		*second = philo->rfork;
	}
}

int	get_forks(t_philosopher *philo)
{
	t_fork	*first;
	t_fork	*second;

	sort_forks(philo, &first, &second);
	if (first == second)
		return (0);
	pthread_mutex_lock(&first->lock);
	log_action(philo, FORK_MSG);
	pthread_mutex_lock(&second->lock);
	log_action(philo, FORK_MSG);
	return (1);
}

void	release_forks(t_philosopher *philo)
{
	t_fork	*first;
	t_fork	*second;

	sort_forks(philo, &first, &second);
	pthread_mutex_unlock(&first->lock);
	pthread_mutex_unlock(&second->lock);
}
