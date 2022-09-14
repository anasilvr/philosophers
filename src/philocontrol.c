/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philocontrol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:09:50 by anarodri          #+#    #+#             */
/*   Updated: 2022/09/14 17:03:38 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_start(t_control *input)
{
	int		i;

	if (input->nb_philo == 1)
	{
		while (input->game_over != TRUE)
		{
			print(&input->philo[0], "has taken a fork");
			ft_sleep(&input->philo[0], input->t_to_die);
			printf("%s", RED);
			print(&input->philo[0], "died \xF0\x9F\x92\x80");
			input->game_over = TRUE;
		}
	}
	else
	{
		i = -1;
		while (++i < input->nb_philo)
			pthread_create(&input->philo[i].tid, NULL, \
			&philo_do, (void *) &input->philo[i]);
		checker(input);
		philo_end(input);
	}
}

void	*philo_do(void *p)
{
	t_philo		*ph;
	t_control	*input;

	ph = (t_philo *)p;
	input = ph->args;
	if (ph->id % 2)
		usleep(150);
	while (input->game_over == FALSE)
	{
		if (input->game_over == TRUE)
			break ;
		if (input->max_meals > 0 && ph->meals_eaten == input->max_meals)
			break ;
		ph_eat(ph);
		ph_think(ph);
		ph_sleep(ph);
	}
	return (NULL);
}

void	checker(t_control *c)
{
	int	i;

	i = 0;
	while (c->game_over == FALSE)
	{
		check_death(c);
		if (c->game_over == TRUE)
			break ;
		if (c->max_meals > 0)
		{
			while (i < c->nb_philo)
			{
				if (c->philo[i].meals_eaten < c->max_meals)
					break ;
				i++;
			}
			if (i == c->nb_philo)
				c->game_over = TRUE;
			usleep(50);
		}
	}
}

void	check_death(t_control *c)
{
	int	i;

	i = 0;
	while (i < c->nb_philo && c->game_over == FALSE)
	{
		pthread_mutex_lock(&c->checker);
		if ((timestamp(c) - c->philo[i].t_lastmeal) >= c->t_to_die)
		{
			printf("%s", RED);
			print(&c->philo[i], " died \xF0\x9F\x92\x80");
			c->game_over = TRUE;
		}
		pthread_mutex_unlock(&c->checker);
		i++;
	}
}

void	philo_end(t_control *input)
{
	int	i;

	i = input->nb_philo;
	while (--i >= 0)
		pthread_join(input->philo[i].tid, NULL);
	while (++i < input->nb_philo)
		pthread_mutex_destroy(&input->fork[i]);
	pthread_mutex_destroy(&input->cout);
	pthread_mutex_destroy(&input->checker);
	free(input->philo);
	free(input->fork);
	free(input);
}
