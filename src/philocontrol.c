/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philocontrol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:09:50 by anarodri          #+#    #+#             */
/*   Updated: 2022/09/20 10:05:12 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_start(t_control *input)
{
	int		i;

	if (input->nb_philo == 1)
	{
		one_philo(input->philo);
	}
	else
	{
		i = -1;
		while (++i < input->nb_philo)
			pthread_create(&input->philo[i].tid, NULL, \
			&philo_do, (void *) &input->philo[i]);
		while (input->game_over == FALSE)
			checker(input);
	}
}

void	*philo_do(void *p)
{
	t_philo		*ph;
	t_control	*input;

	ph = (t_philo *)p;
	input = ph->args;
	if (ph->id % 2)
		usleep(1500);
	while (input->game_over == FALSE)
	{
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
	int	meal_i;
	int	death_i;

	meal_i = 0;
	death_i = 0;
	while (c->game_over == FALSE)
	{
		check_death(&c->philo[death_i]);
		if (c->max_meals > 0)
		{
			while (meal_i < c->nb_philo)
			{
				if (c->philo[meal_i].meals_eaten < c->max_meals)
					break ;
				meal_i++;
			}
			if (meal_i == c->nb_philo)
				c->game_over = TRUE;
		}
		usleep(5000);
		if (death_i == c->nb_philo -1)
			death_i = -1;
		death_i++;
	}
}

void	check_death(t_philo *p)
{
	pthread_mutex_lock(&p->args->checker);
	if ((timestamp(p->args) - p->t_lastmeal) >= p->args->t_to_die)
	{
		print(p, "died \xF0\x9F\x92\x80");
		p->args->game_over = TRUE;
	}
	pthread_mutex_unlock(&p->args->checker);
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
