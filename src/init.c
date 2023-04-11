/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:11:09 by anarodri          #+#    #+#             */
/*   Updated: 2023/04/04 09:45:30 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_argv(int argc, char **argv)
{
	int	i;
	int	res;

	if (argc != 5 && argc != 6)
	{
		printf("%s", ERR_CMD);
		return (-1);
	}
	i = 0;
	while (argv[++i])
	{
		res = ft_atoi(argv[i]);
		if (i == 1 && res >= 201)
		{
			printf(ERR_MAX);
			return (-1);
		}
		if (res <= 0)
		{
			printf(ERR_ARGS);
			return (-1);
		}
	}
	return (0);
}

void	init_s_control(char **argv, t_control *input)
{
	int	i;

	i = -1;
	input->error = FALSE;
	input->game_over = FALSE;
	input->end_meal = 0;
	input->nb_philo = ft_atoi(argv[1]);
	input->t_to_die = ft_atoi(argv[2]);
	input->t_to_eat = ft_atoi(argv[3]);
	input->t_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		input->max_meals = ft_atoi(argv[5]);
	else
		input->max_meals = FALSE;
	input->philo = ft_calloc(input->nb_philo, (sizeof(t_philo)));
	input->fork = ft_calloc(input->nb_philo, (sizeof(pthread_mutex_t)));
	pthread_mutex_init(&input->cout, NULL);
	pthread_mutex_init(&input->checker, NULL);
	while (++i < input->nb_philo)
		pthread_mutex_init(&input->fork[i], NULL);
	init_s_philo(input);
	input->t0 = start_time();
}

void	init_s_philo(t_control *input)
{
	int	i;

	i = 0;
	while (i < input->nb_philo)
	{
		input->philo[i].id = i + 1;
		input->philo[i].meals_eaten = 0;
		input->philo[i].t_lastmeal = 0;
		input->philo[i].l_fork = i;
		input->philo[i].r_fork = (i + 1) % input->nb_philo;
		input->philo[i].args = input;
		i++;
	}
}
