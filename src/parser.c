/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:03:09 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/26 14:38:21 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putstr(char *s)
{
	while (*s)
		write (1, &*s++, 1);
}

bool	parse_number(char	*str, long *ptr)
{
	if (ft_atoi(str) == -1)
	{
		ft_putstr("No input can be negative number");
		return (false);
	}
	else
		*ptr = ft_atoi(str);
	return (true);
}

bool	get_input(int ac, char **av, t_data *data)
{
	if ((ac <= 5 && ac != 5) || (ac > 6 && ac != 6))
	{
		ft_putstr("Expected arguments 4 or 5");
		return (false);
	}
	if (!parse_number(av[1], (long *)&data->n_philos))
		return (false);
	if (data->n_philos < 1)
	{
		ft_putstr("There should be at least 1 philo");
		return (false);
	}
	if (!parse_number(av[2], &data->time_to_die))
		return (false);
	if (!parse_number(av[3], &data->time_to_eat))
		return (false);
	if (!parse_number(av[4], &data->time_to_sleep))
		return (false);
	if (ac == 6)
	{
		if (!parse_number(av[5], (long *)&data->num_meals))
			return (false);
	}
	return (true);
}
