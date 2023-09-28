/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 15:05:22 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/26 13:56:27 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_fork_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mut_last_eat_time);
	}
}

bool	create_fork_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			destroy_fork_mutexes(data);
			return (false);
		}
		if (pthread_mutex_init(&data->philos[i].mut_last_eat_time, NULL))
		{
			destroy_fork_mutexes(data);
			return (false);
		}
	}
	return (true);
}

void	destroy_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->mut_print);
	pthread_mutex_destroy(&data->num_philo_full_mutex);
	pthread_mutex_destroy(&data->is_end_mutex);
	pthread_mutex_destroy(&data->start_simulation_mutex);
	destroy_fork_mutexes(data);
}

bool	create_mutexes(t_data *data)
{
	pthread_mutex_init(&data->mut_print, NULL);
	if (pthread_mutex_init(&data->num_philo_full_mutex, NULL))
	{
		pthread_mutex_destroy(&data->mut_print);
		return (false);
	}
	if (pthread_mutex_init(&data->is_end_mutex, NULL))
	{
		pthread_mutex_destroy(&data->mut_print);
		pthread_mutex_destroy(&data->num_philo_full_mutex);
		return (false);
	}
	if (pthread_mutex_init(&data->start_simulation_mutex, NULL))
	{
		pthread_mutex_destroy(&data->mut_print);
		pthread_mutex_destroy(&data->num_philo_full_mutex);
		pthread_mutex_destroy(&data->is_end_mutex);
		return (false);
	}
	if (!create_fork_mutexes(data))
	{
		destroy_mutexes(data);
		return (false);
	}
	return (true);
}
