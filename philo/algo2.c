/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 10:40:05 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/20 16:58:56 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	unlock_mutexex(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (1);
}

int	odd_philos(t_philo *philo)
{
	int	status;

	if (philo->params->nb_philo == 1)
		return (one_philo(philo));
	if (!not_dead(philo, philo->params))
		return (1);
	pthread_mutex_lock(philo->left_fork);
	if (!not_dead(philo, philo->params))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	writer(philo, 4);
	pthread_mutex_lock(philo->right_fork);
	update_last_meal(philo);
	if (!not_dead(philo, philo->params))
		return (unlock_mutexex(philo));
	writer(philo, 4);
	writer(philo, 0);
	status = ft_usleep(philo->params->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (status);
}

int	one_philo(t_philo *philo)
{
	int	status;

	if (!not_dead(philo, philo->params))
		return (1);
	pthread_mutex_lock(philo->left_fork);
	if (!not_dead(philo, philo->params))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	writer(philo, 4);
	if (!not_dead(philo, philo->params))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	writer(philo, 4);
	status = ft_usleep(philo->params->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	return (status);
}

int	even_philos(t_philo *philo)
{
	int	status;

	if (!not_dead(philo, philo->params))
		return (1);
	pthread_mutex_lock(philo->right_fork);
	if (!not_dead(philo, philo->params))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	writer(philo, 4);
	pthread_mutex_lock(philo->left_fork);
	update_last_meal(philo);
	if (!not_dead(philo, philo->params))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	writer(philo, 4);
	writer(philo, 0);
	status = ft_usleep(philo->params->time_to_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (status);
}

void	*reached_nbom(t_params *params, int y)
{
	pthread_mutex_lock(&params->read_flag_death);
	params->death = 1;
	pthread_mutex_unlock(&params->read_flag_death);
	pthread_mutex_unlock(&params->tab_of_philo[y].last_meal);
	return (NULL);
}
