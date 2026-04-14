/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:52:29 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/14 15:37:01 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(void *arg)
{
	t_params	*params;
	int			y;

	y = 0;
	params = (t_params *)arg;
	while (y < params->nb_philo)
	{
		if (params->tab_of_philo[y].time_lm - get_time_of_day_ms() > params->time_to_die)
		{
			pthread_mutex_lock(&params->read_flag_death);
			params->death = 1;
			pthread_mutex_unlock(&params->read_flag_death);
		}
		y++;
	}
	return NULL;
}
