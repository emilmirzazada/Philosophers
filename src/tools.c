/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:35:19 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/26 18:48:40 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	ft_set_last_eat_time(t_phil *phil)
{
	pthread_mutex_lock(&phil->mut_last_eat_time);
	phil->last_eat_time = get_time();
	pthread_mutex_unlock(&phil->mut_last_eat_time);
	return (0);
}

int	print_msg(t_phil *phil, char *msg, bool is_end)
{
	long int	time;

	if (is_end_of_simulation(phil) != 1 || is_end)
	{
		time = get_time() - phil->data->start_time;
		pthread_mutex_lock(&phil->data->mut_print);
		if (is_end_of_simulation(phil) != 1 || is_end)
			printf("%lu %d %s\n", time, phil->id, msg);
		pthread_mutex_unlock(&phil->data->mut_print);
	}
	return (0);
}

int	ft_check_if_dead(t_phil *phil)
{
	long int	last_eat_time;

	pthread_mutex_lock(&phil->mut_last_eat_time);
	last_eat_time = phil->last_eat_time;
	pthread_mutex_unlock(&phil->mut_last_eat_time);
	if (get_time() - last_eat_time > phil->data->time_to_die)
		return (1);
	else
		return (0);
}

bool	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (true);
	return (false);
}

long int	ft_atoi(const char *str)
{
	long int	tmp;
	long int	result;

	result = 0;
	while (*str != '\0' && (*str == ' ' || *str == '\f' || *str == '\n'
			|| *str == '\r' || *str == '\t' || *str == '\v'))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (-1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		tmp = result * 10 + (*str++ - '0');
		if (tmp > INT_MAX - 1)
			return (-1);
		result = tmp;
	}
	return (result);
}
