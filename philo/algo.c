/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 11:18:33 by anis              #+#    #+#             */
/*   Updated: 2026/04/16 23:50:31 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_threads(t_philo *philo, t_params *params)
{
	int	y;

	y = 0;
	// printf("je suis ici donc le segfault viens apres\n");
	while (y < params->nb_philo)
	{
		//philo->time_lm = get_time_of_day_ms();
		pthread_create(&philo[y].thread, NULL, &algo, philo + y);
		// printf("thread number %d launched\n", y);
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
		usleep(10000);
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
			printf("%ld: philo number %d is sleeping\n", get_time_of_day_ms(), philo->id);
			ft_usleep(philo->params->time_to_sleep * 1000, philo);
		}
		else
		{
			//printf("salut philo\n");
			break;
		}
		//printf("je suis ici par la\n");
		ft_usleep(((philo->params->time_to_die - (philo->params->time_to_eat + philo->params->time_to_sleep)) / 2) * 1000, philo);
		printf("%ld: philo number %d is thinking\n", get_time_of_day_ms(), philo->id);
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

	printf("%ld: le philo number %d tente de prendre la fourchette de gauche\n", get_time_of_day_ms(), philo->id);
	pthread_mutex_lock(philo->left_fork);
	printf("%ld: le philo number %d tente de prendre la fourchette de droite\n", get_time_of_day_ms(), philo->id);
	pthread_mutex_lock(philo->right_fork);
	update_last_meal(philo);
	printf("%ld: philo number %d is eating\n", get_time_of_day_ms(), philo->id);
	status = ft_usleep(philo->params->time_to_eat * 1000, philo);
	pthread_mutex_unlock(philo->left_fork); // update le temps du last meal
	pthread_mutex_unlock(philo->right_fork); // update le temps du last meal
	return (status);
}

int	even_philos(t_philo *philo)
{
	int	status;

	printf("%ld: le philo number %d tente de prendre la fourchette de droite\n", get_time_of_day_ms(), philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("%ld: le philo number %d tente de prendre la fourchette de gauche\n", get_time_of_day_ms(), philo->id);
	pthread_mutex_lock(philo->left_fork);
	update_last_meal(philo);
	printf("%ld: philo number %d is eating\n", get_time_of_day_ms(), philo->id);
	status = ft_usleep(philo->params->time_to_eat * 1000, philo);
	pthread_mutex_unlock(philo->right_fork); // update le temps du last meal
	pthread_mutex_unlock(philo->left_fork);
	return (status);
}
