/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:11:09 by anarodri          #+#    #+#             */
/*   Updated: 2022/09/13 16:23:51 by anarodri         ###   ########.fr       */
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
		if (i == 1 && res > MAX_PH)
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

t_control	init_s_control(char **argv)
{
	t_control	input;

	input.error = FALSE;
	input.game_over = FALSE;
	input.t0 = start_time();
	input.nb_philo = ft_atoi(argv[1]);
	input.t_to_die = ft_atoi(argv[2]);
	input.t_to_eat = ft_atoi(argv[3]);
	input.t_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		input.max_meals = ft_atoi(argv[5]);
	else
		input.max_meals = FALSE;
	ft_bzero(input.philo, MAX_PH);
	ft_bzero(input.fork, MAX_PH);
	init_mutexes(&input);
	init_s_philo(&input);
	return (input);
}

void	init_mutexes(t_control *input)
{
	int	i;

	if (pthread_mutex_init(&input->cout, NULL) != 0)
	{
		printf("Mutex error! @input->cout");
		input->error = -1;
	}
	i = 0;
	while (i < input->nb_philo)
	{
		if (pthread_mutex_init(&input->fork[i], NULL) != 0)
		{
			printf("Mutex error! @input->fork[%i]", i);
			input->error = -1;
		}
		i++;
	}
	if (pthread_mutex_init(&input->checker, NULL) != 0)
	{
		printf("Mutex error! @input->checker");
		input->error = -1;
	}
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
		input->philo[i].is_full = FALSE;
		input->philo[i].args = input;
		i++;
	}
}
