/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoacts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:52:48 by anarodri          #+#    #+#             */
/*   Updated: 2022/09/13 14:54:34 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ph_take_fork(t_philo *ph)
{
	int	left;
	int	right;

	left = -1;
	right = -1;
	left = pthread_mutex_lock(&ph->args->fork[ph->l_fork]);
	right = pthread_mutex_lock(&ph->args->fork[ph->r_fork]);
	if ((left == 0 && right == 0) && ph->args->game_over != TRUE)
	{
		print(ph, "has taken a fork");
		print(ph, "has taken a fork");
		return (TRUE);
	}
	else
	{
		if (left == 0)
			pthread_mutex_unlock(&ph->args->fork[ph->l_fork]);
		if (right == 0)
			pthread_mutex_unlock(&ph->args->fork[ph->r_fork]);
		return (FALSE);
	}
}

void	ph_eat(t_philo *ph)
{
	if (ph->is_full != TRUE && ph->args->game_over != TRUE)
	{
		print(ph, "is eating \xF0\x9F\x8D\x9D");
		ft_sleep(ph, ph->args->t_to_eat);
		ph->t_lastmeal = timestamp(ph->args);
		ph->meals_eaten += 1;
		pthread_mutex_unlock(&ph->args->fork[ph->l_fork]);
		pthread_mutex_unlock(&ph->args->fork[ph->r_fork]);
		if (ph->args->max_meals > 0 && ph->meals_eaten == ph->args->max_meals)
			ph->is_full = TRUE;
	}
}
