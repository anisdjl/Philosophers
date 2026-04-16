/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 15:30:04 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/17 00:02:56 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	not_dead(t_philo *philo, t_params *params)
{
	// c'est lui qui verifie si le philo est encore ne vie
	long	difference;
	long	actual_time;

	actual_time = get_time_of_day_ms();
	difference = time_last_meal(actual_time, philo);
	if (difference >= params->time_to_die)
	{
		printf("%ld: philo numeber %d is dead\n", get_time_of_day_ms(), philo->id);
		return (0);
	}
	else
		return (1);
}

long	get_time_of_day_ms(void)
{
	// il calcule le temps actuel (il faut un ft_usleep aussi)
	struct timeval	start;
	long			return_value;

	gettimeofday(&start, NULL);
	return_value = ((start.tv_sec * 1000) + (start.tv_usec / 1000));
	return (return_value);
}

long	time_last_meal(int time, t_philo *philo)
{
	// renvoi le temps depuis le dernier repas pour le superviseur
	long	difference;
	
	pthread_mutex_lock(&philo->last_meal);
	difference = time - philo->time_lm;
	pthread_mutex_unlock(&philo->last_meal);
	return (difference);
}

int	ft_usleep(int time_to_sleep, t_philo *philo)
{
	long	target;

	target = get_time_of_day_ms() + time_to_sleep;
	while(get_time_of_day_ms() < target) // ici on mettra les calcul pour sacoir combien il doit dormir
	{
		pthread_mutex_lock(&philo->params->read_flag_death);
		if (philo->params->death == 1)
		{
			pthread_mutex_unlock(&philo->params->read_flag_death);	
			return (1);
		}
		pthread_mutex_unlock(&philo->params->read_flag_death);
		usleep(500); // faut pas laisser les 500 c'est pas bon 
	}
	return (0);
}

void	wait_all_threads(t_params *params, t_philo *philo)
{
	int	y;
	
	y = 0;
	while (y < params->nb_philo)
	{
		pthread_join(philo[y].thread, NULL);
		y++;
	}
	pthread_join(params->thread_supervisor, NULL);
	return ;
}
