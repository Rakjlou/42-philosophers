/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 23:38:33 by nsierra-          #+#    #+#             */
/*   Updated: 2022/02/07 20:57:55 by nsierra-         ###   ########.fr       */
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
