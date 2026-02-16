/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 12:23:54 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/16 13:13:43 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	test_num(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (ft_isdigit(ft_atoi(argv[i])) || ft_atoi(argv[i]) <= 0)
		{
			printf("invalid arguments\n");	
			return (0);
		}
		else
			i++;
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	y;
	int	sign;
	int	total;

	total = 0;
	sign = 1;
	y = 0;
	while ((nptr[y] >= 9 && nptr[y] <= 13) || nptr[y] == 32)
		y++;
	if (nptr[y] == '-')
	{
		sign = -sign;
		y++;
	}
	else if (nptr[y] == '+')
		y++;
	while (nptr[y] >= '0' && nptr[y] <= '9')
	{
		total = total * 10 + nptr[y] - '0';
		y++;
	}
	return (total * sign);
}
