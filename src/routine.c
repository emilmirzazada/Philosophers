/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:13:41 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/28 12:44:16 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_end_of_simulation(t_phil *phil)
{
	int	res;

	pthread_mutex_lock(&phil->data->is_end_mutex);
	res = phil->data->is_end;
	pthread_mutex_unlock(&phil->data->is_end_mutex);
	return (res);
}

bool	death_routine(void *v_data)
{
	t_data	*data;
	int		i;

	data = (t_data *)v_data;
	i = 0;
	while (i < data->n_philos)
	{
		if (ft_check_if_dead(&data->philos[i]) == 1)
		{
			pthread_mutex_lock(&data->is_end_mutex);
			data->is_end = 1;
			pthread_mutex_unlock(&data->is_end_mutex);
			pthread_mutex_lock(&data->num_philo_full_mutex);
			if (data->num_philo_full != data->n_philos)
				print_msg(&data->philos[i], "died", true);
			pthread_mutex_unlock(&data->num_philo_full_mutex);
			return (true);
		}
		i++;
	}
	return (false);
}

void	wait_for_simulation_start(t_data *data)
{
	pthread_mutex_lock(&data->start_simulation_mutex);
	pthread_mutex_unlock(&data->start_simulation_mutex);
}

void	*routine(void *v_philo)
{
	t_phil	*philo;

	philo = (t_phil *) v_philo;
	wait_for_simulation_start(philo->data);
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (is_end_of_simulation(philo) != 1)
	{
		if (ft_eat(philo) != 0)
			break ;
		if (is_end_of_simulation(philo) == 1)
			break ;
		ft_sleep(philo);
		if (is_end_of_simulation(philo) == 1)
			break ;
		ft_think(philo);
	}
	return (NULL);
}
