/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emirzaza <emirzaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:28:18 by emirzaza          #+#    #+#             */
/*   Updated: 2023/09/26 13:41:32 by emirzaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_phil
{
	int				id;
	int				num_philos;
	int				meals_eaten;
	long int		last_eat_time;
	pthread_mutex_t	mutex_num_meals;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	mut_last_eat_time;
	t_data			*data;
}					t_phil;

typedef struct s_data
{
	int					id;
	int					n_philos;
	int					num_meals;
	int					num_philo_full;
	int					is_end;
	long int			start_time;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	t_phil				*philos;
	pthread_t			*philo_ths;
	pthread_mutex_t		num_philo_full_mutex;
	pthread_mutex_t		*forks;
	pthread_mutex_t		mut_print;
	pthread_mutex_t		is_end_mutex;
	pthread_mutex_t		start_simulation_mutex;
}						t_data;

bool		get_input(int ac, char **av, t_data *data);
bool		init_data(t_data *data);
void		dealloc_data(t_data *data);

void		init_forks(t_data *data);
int			take_forks(t_phil *phil);
int			release_forks(t_phil *phil);

int			ft_eat(t_phil *phil);
int			ft_sleep(t_phil *phil);
int			ft_think(t_phil *phil);

bool		start_philos(t_data *data);
void		join_threads(t_data *data);
bool		create_mutexes(t_data *data);
void		destroy_mutexes(t_data *data);

int			is_end_of_simulation(t_phil *phil);
int			print_msg(t_phil *phil, char *msg, bool is_end);

long int	ft_set_last_eat_time(t_phil *phil);
void		*routine(void *v_philo);
bool		death_routine(void *v_data);

int			ft_check_if_dead(t_phil *phil);
long int	get_time(void);
void		ft_usleep(long int sleep_time);
long int	ft_atoi(const char *str);

#endif