/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:47:25 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/28 12:32:22 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	join_threads(t_data *data)
{
	int	i;

	while (1)
	{
		if (death_routine(data) == true)
			break ;
		ft_usleep(1);
	}
	i = 0;
	while (i < data->n_philos)
		pthread_join(data->philo_ths[i++], NULL);
}

void	set_last_meal_time_all_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_lock(&(data->philos[i].mut_last_eat_time));
		data->philos[i].last_eat_time = data->start_time;
		pthread_mutex_unlock(&(data->philos[i].mut_last_eat_time));
		i++;
	}
}

bool	start_simulation(t_data *data)
{
	pthread_mutex_lock(&data->start_simulation_mutex);
	if (!start_philos(data))
		return (false);
	data->start_time = get_time();
	set_last_meal_time_all_philos(data);
	pthread_mutex_unlock(&data->start_simulation_mutex);
	return (true);
}

int	main(int ac, char **av)
{
	t_data		data;

	if (!get_input(ac, av, &data))
		return (1);
	if (!init_data(&data))
		return (1);
	init_forks(&data);
	if (!start_simulation(&data))
		return (1);
	join_threads(&data);
	destroy_mutexes(&data);
	dealloc_data(&data);
	return (0);
}
