/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philocontrol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:09:50 by anarodri          #+#    #+#             */
/*   Updated: 2022/09/13 16:32:09 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_start(t_control *input)
{
	int		i;
	t_philo	*ph;

	ph = input->philo;
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
			pthread_create(&(ph[i].tid), NULL, (void *) philo_do, &(ph[i]));
		checker(input);
		philo_end(input);
	}
}

void	philo_do(void *p)
{
	t_philo		*ph;
	t_control	*input;

	ph = (t_philo *)p;
	input = ph->args;
	if (ph->id % 2)
		usleep(100);
	while (input->game_over != TRUE)
	{
		printf("----> Game over value from routine: %d\n", input->game_over);
		while (!ph_take_fork(ph))
			usleep(5);
		ph_eat(ph);
		if (ph->is_full == TRUE)
			break ;
		print(ph, "is thinking \xF0\x9F\x92\xAD");
		print(ph, "is sleeping \xF0\x9F\x92\xA4");
		ft_sleep(ph, input->t_to_sleep);
	}
}

void	checker(t_control *c)
{
	int	i;

	while (c->game_over != TRUE)
	{
		i = -1;
		while (++i < c->nb_philo && c->game_over != TRUE)
		{
			pthread_mutex_lock(&c->checker);
			if ((timestamp(c) - c->philo[i].t_lastmeal) > c->t_to_die)
			{
				c->game_over = TRUE;
				printf("----> Game over value from checker: %d\n", c->game_over);
				printf("%s", RED);
				print(c->philo, "died \xF0\x9F\x92\x80");
			}
			pthread_mutex_unlock(&c->checker);
			usleep(100);
		}
		if (c->game_over == TRUE)
			break ;
		i = 0;
		while (i < c->nb_philo && c->philo[i].meals_eaten >= c->max_meals - 1)
			i++;
		if (i == c->nb_philo && c->max_meals == TRUE)
			c->game_over = TRUE;
	}
	printf("\t-----> SALUT Philo nb: %d\n", c->philo->id);
}

void	philo_end(t_control *input)
{
	int	i;
	i = input->nb_philo;
	while (--i >= 0)
	{
		pthread_join(input->philo[i].tid, NULL);
			printf("\t-----> C'EST LA FIIIIN! Philo nb: %d\n", input->philo->id);
	}
	while (++i < input->nb_philo)
		pthread_mutex_destroy(&input->fork[i]);
	pthread_mutex_destroy(&input->cout);
	pthread_mutex_destroy(&input->checker);
}
