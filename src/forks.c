/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:45:05 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/28 12:43:23 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_phil *phil)
{
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(phil->left_f);
		print_msg(phil, "has taken a fork", false);
		pthread_mutex_lock(phil->right_f);
		print_msg(phil, "has taken a fork", false);
	}
	else
	{
		pthread_mutex_lock(phil->right_f);
		print_msg(phil, "has taken a fork", false);
		if (phil->data->n_philos == 1)
		{
			pthread_mutex_unlock(phil->right_f);
			return (1);
		}
		pthread_mutex_lock(phil->left_f);
		print_msg(phil, "has taken a fork", false);
	}
	return (0);
}

int	release_forks(t_phil *phil)
{
	pthread_mutex_unlock(phil->left_f);
	pthread_mutex_unlock(phil->right_f);
	return (0);
}
