/*
//  philosophe.c
//  Philo1
//
//  Created by quentin PIDOUX on 13/03/12.
//  Copyright (c) 2012 EPITECH. All rights reserved.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "philosophe.h"

philosophe **init_philos(baguette **bags, int *quantity)
{
  int	i = 0;
  philosophe **philos;

  philos = malloc(8 * sizeof(philosophe*));
  philos[7] = NULL;
  while (i != 7){
      philos[i] = malloc(sizeof(philosophe));
      philos[i]->thread = malloc(sizeof(pthread_t));
      philos[i]->id = i;
      if (i == 0)
        philos[i]->right = bags[6];
      else
        philos[i]->right = bags[i - 1];
      philos[i]->left = bags[i];
      philos[i]->if_right = 0;
      philos[i]->if_left = 0;
      philos[i]->quantity_eat = 0;
      philos[i]->quantity = quantity;
      i++;
    }
  return philos;
}

baguette **init_bags()
{
  int	i = 0;
  baguette **bags;

  bags = malloc(8 * sizeof(baguette*));
  bags[7] = NULL;
  while (i != 7){
      bags[i] = malloc(sizeof(baguette));
      bags[i]->mutex = malloc(sizeof(pthread_mutex_t));
      pthread_mutex_init(bags[i]->mutex, NULL);
      bags[i]->is_used = 0;
      i++;
    }
  return bags;
}

void	free_all(int *quantity, baguette **bags, philosophe **philos)
{
  int	i = 0;
  
  free(quantity);
  while (bags[i])
    free_baguette(bags[i++]);
  free(bags);
  i = 0;
  while (bags[i])
    free_philosophe(philos[i++]);
  free(philos);
}

int	main(int argc, char **argv)
{
  philosophe	**philos;
  baguette      **bags = init_bags();
  int           i = argc = 0;
  void          *ret;
  int           *quantity = malloc(sizeof(int));
  if (!argv[1])
    *quantity = 100;
  else
    *quantity = atoi(argv[1]);
  printf("\nrice quantity : %d.\n\n", *quantity);
  philos = init_philos(bags, quantity);
  while (philos[i]){
      if (philos[i]->id % 2)
	pthread_create(philos[i]->thread, NULL, &take_right, (void*)philos[i]);
      else
	pthread_create(philos[i]->thread, NULL, &take_left, (void*)philos[i]);
      i++;
    }
  i = 0;
  while (philos[i])
    pthread_join(*(philos[i++]->thread), &ret);
  free_all(quantity, bags, philos);
  return (0);
}
