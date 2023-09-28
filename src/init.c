/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:34:21 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/26 19:04:20 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	malloc_data(t_data *data)
{
	data->philo_ths = malloc(sizeof(pthread_t) * data->n_philos);
	if (!(data->philo_ths))
		return (false);
	data->philos = malloc(sizeof(t_phil) * data->n_philos);
	if (!(data->philos))
		return (false);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!(data->forks))
		return (false);
	return (true);
}

void	dealloc_data(t_data *data)
{
	free(data->philo_ths);
	data->philo_ths = NULL;
	free(data->philos);
	data->philos = NULL;
	free(data->forks);
	data->forks = NULL;
}

bool	init_data(t_data *data)
{
	int	i;

	if (!malloc_data(data))
		return (false);
	if (!create_mutexes(data))
	{
		dealloc_data(data);
		return (false);
	}
	i = -1;
	while (++i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		ft_set_last_eat_time(&data->philos[i]);
	}
	return (true);
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->philos[0].left_f = &data->forks[0];
	data->philos[0].right_f = &data->forks[data->n_philos - 1];
	while (++i < data->n_philos)
	{
		data->philos[i].left_f = &data->forks[i];
		data->philos[i].right_f = &data->forks[i - 1];
	}
}

bool	start_philos(t_data *data)
{
	int	i;

	data->is_end = 0;
	data->num_philo_full = 0;
	i = -1;
	while (++i < data->n_philos)
	{
		data->philos[i].data = data;
		data->philos[i].meals_eaten = 0;
		if (pthread_create(&data->philo_ths[i], NULL, &routine,
				&data->philos[i]))
		{
			pthread_mutex_lock(&data->is_end_mutex);
			data->is_end = 1;
			pthread_mutex_unlock(&data->is_end_mutex);
			join_threads(data);
			destroy_mutexes(data);
			dealloc_data(data);
			return (false);
		}
	}
	return (true);
}
