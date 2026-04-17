/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:52:29 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/17 17:45:02 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor(void *arg)
{
	t_params	*params;
	int			y;

	y = 0;
	params = (t_params *)arg;
	while (1)
	{
		y = 0;
		while (y < params->nb_philo)
		{
			pthread_mutex_lock(&params->tab_of_philo[y].last_meal);
			//printf("Debug: Philo %d | Now: %ld | Last: %ld | Diff: %ld\n", 
    		//y + 1, get_time_of_day_ms(), params->tab_of_philo[y].time_lm, 
    		//get_time_of_day_ms() - params->tab_of_philo[y].time_lm);
			if (get_time_of_day_ms() - params->tab_of_philo[y].time_lm > params->time_to_die)
			{
				pthread_mutex_lock(&params->read_flag_death);
				params->death = 1;
				pthread_mutex_unlock(&params->read_flag_death);
				printf("%ld: philo number %d is dead dans le supervisor\n", get_time_of_day_ms() - params->start_time, y + 1);
				pthread_mutex_unlock(&params->tab_of_philo[y].last_meal);
				return NULL;
			}
			pthread_mutex_unlock(&params->tab_of_philo[y].last_meal);
			y++;
		}
		// usleep(1000);
	}
	return NULL;
}
