/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:18:33 by anis              #+#    #+#             */
/*   Updated: 2026/04/13 17:21:02 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_threads(t_philo **philo, t_params *params)
{
	int	y;

	y = 0;

	while (y < params->nb_philo)
	{
		pthread_create(&philo[y], NULL, &algo, philo[y]);
		y++;
	}
	pthread_create(params->thread_supervisor, NULL, &supervisor, params);
}

void	algo(void *arg)
{
	t_philo	*philo;
	int		status;
	
	philo = (t_philo *)arg;
	while (1)
	{
		if (!not_dead(philo, philo->params))
			break ;
		pthread_mutex_lock(philo->left_fork);
		status = ft_usleep(philo->params->time_to_eat);
		pthread_mutex_unlock(philo->left_fork); // update le temps du last meal
		if (status == 0)
			ft_usleep(philo->params->time_to_sleep);
		else
			break;
	}
	return ; // pas sur de laisser ca ici
}

