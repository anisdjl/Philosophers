/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dice.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjelili <adjelili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 18:43:54 by adjelili          #+#    #+#             */
/*   Updated: 2026/02/13 21:31:42 by adjelili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


void	*randooooom()
{
	int *res;
	int resultat = (rand() % 6) + 1;
	
	res = malloc(sizeof(int));
	*res = resultat;
	
	return ((void*) res);
}

int main(void)
{
	int y;
	int *res;
	pthread_t threads[24];
	int i;
	
	i = 0;
	srand(time(NULL));
	y = 0;
	while (y < 24)
	{
		if (pthread_create(threads + y, NULL, &randooooom, NULL) != 0)
		{
			printf("error\n");
			return (0);
		}
		y++;
	}
	y = 0;
	while (y < 24)
	{
		if (pthread_join(threads[y], (void **) &res))
		{
			return (0);
		}
		y++;
		printf("%d : %d\n", i,*res);
		i++;
	}
	
	return (0);
}