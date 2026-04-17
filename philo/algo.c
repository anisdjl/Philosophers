/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:18:33 by anis              #+#    #+#             */
/*   Updated: 2026/04/17 17:53:31 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_threads(t_philo *philo, t_params *params)
{
	int	y;

	y = 0;
	while (y < params->nb_philo)
	{
		pthread_create(&philo[y].thread, NULL, &algo, philo + y);
		y++;
	}
	pthread_create(&params->thread_supervisor, NULL, &supervisor, params);
}

void	*algo(void *arg)
{
	t_philo	*philo;
	int		status;
	
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (!not_dead(philo, philo->params) || (philo->params->notepme > 0
			&& philo->number_of_meal == philo->params->notepme))
			break ;
		if (philo->id % 2 == 0)
			status = even_philos(philo);
		else
			status = odd_philos(philo);
		if (status == 0)
		{
			printf("%ld: philo number %d is sleeping\n", get_time_of_day_ms() - philo->params->start_time, philo->id);
			ft_usleep(philo->params->time_to_sleep, philo);
		}
		else
			break;
		ft_usleep(((philo->params->time_to_die - (philo->params->time_to_eat + philo->params->time_to_sleep)) / 2), philo);
		printf("%ld: philo number %d is thinking\n", get_time_of_day_ms() - philo->params->start_time, philo->id);
		philo->number_of_meal++;
	}
	return NULL;
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal);
	philo->time_lm = get_time_of_day_ms();
	pthread_mutex_unlock(&philo->last_meal);
}

int	odd_philos(t_philo *philo)
{
	int status;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	update_last_meal(philo);
	printf("%ld: philo number %d is eating\n", get_time_of_day_ms() - philo->params->start_time, philo->id);
	status = ft_usleep(philo->params->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (status);
}

int	even_philos(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	update_last_meal(philo);
	printf("%ld: philo number %d is eating\n", get_time_of_day_ms() - philo->params->start_time, philo->id);
	status = ft_usleep(philo->params->time_to_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (status);
}
