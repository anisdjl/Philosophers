/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:30:04 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/13 15:30:25 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	not_dead(t_philo *philo, t_params *params)
{
	// c'est lui qui verifie si le philo est encore ne vie
	int difference;
	int	actual_time;

	actual_time = get_time_of_day_ms();
	difference = time_last_meal(actual_time, philo);
}

int	get_time_of_day_ms(void)
{
	// il calcule le temps actuel (il faut un ft_usleep aussi)
	struct timeval	start;
	int				return_value;

	gettimeofday(&start, NULL);
	return_value = (start.tv_sec * 1000);
	return (return_value);
}

int	time_last_meal(int time, t_philo *philo)
{
	// renvoi le temps depuis le dernier repas pour le superviseur
	int	difference;
	
	pthread_mutex_lock(&philo->last_meal);
	difference = philo->time_lm - time;
	pthread_mutex_unlock(&philo->last_meal);
	return (difference);
}
