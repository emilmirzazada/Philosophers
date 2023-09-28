/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:36:56 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/26 14:38:39 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	increment_meals_eaten(t_phil *phil)
{
	phil->meals_eaten++;
	if (phil->meals_eaten == phil->data->num_meals)
	{
		pthread_mutex_lock(&phil->data->num_philo_full_mutex);
		phil->data->num_philo_full++;
		if (phil->data->num_philo_full == phil->data->n_philos)
		{
			pthread_mutex_lock(&phil->data->is_end_mutex);
			phil->data->is_end = 1;
			pthread_mutex_unlock(&phil->data->is_end_mutex);
		}
		pthread_mutex_unlock(&phil->data->num_philo_full_mutex);
	}
}

int	ft_eat(t_phil *phil)
{
	if (take_forks(phil) != 0)
		return (1);
	print_msg(phil, "is eating", false);
	ft_set_last_eat_time(phil);
	ft_usleep(phil->data->time_to_eat);
	increment_meals_eaten(phil);
	release_forks(phil);
	return (0);
}

int	ft_sleep(t_phil *phil)
{
	print_msg(phil, "is sleeping", false);
	ft_usleep(phil->data->time_to_sleep);
	return (0);
}

int	ft_think(t_phil *phil)
{
	print_msg(phil, "is thinking", false);
	return (0);
}
