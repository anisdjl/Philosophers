/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:18:33 by anis              #+#    #+#             */
/*   Updated: 2026/04/20 16:54:12 by adjelili         ###   ########.fr       */
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

int	manage_odd_even(t_philo *philo)
{
	int	status;

	if (philo->id % 2 == 0)
		status = even_philos(philo);
	else
		status = odd_philos(philo);
	return (status);
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
		if (!not_dead(philo, philo->params))
			break ;
		status = manage_odd_even(philo);
		if (status == 0 && not_dead(philo, philo->params))
		{
			writer(philo, 1);
			ft_usleep(philo->params->time_to_sleep, philo);
		}
		else
			break ;
		if (!not_dead(philo, philo->params))
			break ;
		(writer(philo, 2), (philo->number_of_meal += 1));
		ft_usleep(((philo->params->time_to_die - (philo->params->time_to_eat
						+ philo->params->time_to_sleep)) / 2), philo);
	}
	return (NULL);
}

void	update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal);
	philo->time_lm = get_time_of_day_ms();
	pthread_mutex_unlock(&philo->last_meal);
}
