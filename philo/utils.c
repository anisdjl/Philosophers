/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anis <anis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 12:23:54 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/16 19:23:39 by anis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	test_digit(int argc, char **argv)
{
	int	y;
	int	a;

	y = 1;
	while (y < argc)
	{
		a = 0;
		while (argv[y][a])
		{
			if (!ft_isdigit((argv[y][a])))
				return (0);
			a++;
		}
		y++;
	}
	return (1);
}

int	test_num(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!test_digit(argc, argv) || ft_atoi(argv[i]) <= 0)
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
