/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:52:29 by adjelili          #+#    #+#             */
/*   Updated: 2026/04/20 11:00:21 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	unlock_supervisor(t_params *params, int y)
{
	pthread_mutex_lock(&params->read_flag_death);
	params->death = 1;
	pthread_mutex_unlock(&params->read_flag_death);
	writer(&params->tab_of_philo[y], 3);
	pthread_mutex_unlock(&params->tab_of_philo[y].last_meal);
	return (NULL);
}

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
			if (check_nbom_supervisor(params))
				return (NULL);
			pthread_mutex_lock(&params->tab_of_philo[y].last_meal);
			if (get_time_of_day_ms() - params->tab_of_philo[y].time_lm
				> params->time_to_die)
			{
				unlock_supervisor(params, y);
				return (NULL);
			}
			pthread_mutex_unlock(&params->tab_of_philo[y].last_meal);
			y++;
		}
	}
	return (NULL);
}

int	check_nbom_supervisor(t_params *params)
{
	int	y;

	y = 0;
	while (y < params->nb_philo)
	{
		pthread_mutex_lock(&params->mutex_nbom);
		if (params->tab_of_philo[y].number_of_meal != params->notepme)
		{
			pthread_mutex_unlock(&params->mutex_nbom);
			return (1);
		}
		pthread_mutex_unlock(&params->mutex_nbom);
		y++;
	}
	return (0);
}

int	check_nbom(t_philo *philo)
{
	int	return_value;

	pthread_mutex_lock(&philo->params->mutex_nbom);
	if (philo->number_of_meal == philo->params->notepme)
		return_value = 1;
	else
		return_value = 0;
	pthread_mutex_unlock(&philo->params->mutex_nbom);
	return (return_value);
}

void	writer(t_philo *philo, int n)
{
	pthread_mutex_lock(&philo->params->mutex_log);
	if (n == 0)
		printf("%ld: philo number %d is eating\n",
			get_time_of_day_ms() - philo->params->start_time, philo->id);
	else if (n == 1)
		printf("%ld: philo number %d is sleeping\n",
			get_time_of_day_ms() - philo->params->start_time, philo->id);
	else if (n == 2)
		printf("%ld: philo number %d is thinking\n",
			get_time_of_day_ms() - philo->params->start_time, philo->id);
	else if (n == 3)
		printf("%ld: philo number %d is dead dans le supervisor\n",
			get_time_of_day_ms() - philo->params->start_time, philo->id);
	else if (n == 4)
		printf("%ld: philo number %d has taken a fork\n",
			get_time_of_day_ms() - philo->params->start_time, philo->id);
	pthread_mutex_unlock(&philo->params->mutex_log);
	return ;
}
