/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoacts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:52:48 by anarodri          #+#    #+#             */
/*   Updated: 2022/09/14 17:04:47 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ph_eat(t_philo *ph)
{
	if (ph->args->game_over == FALSE)
	{
		pthread_mutex_lock(&ph->args->fork[ph->l_fork]);
		print(ph, "has taken a fork");
		pthread_mutex_lock(&ph->args->fork[ph->r_fork]);
		print(ph, "has taken a fork");
		print(ph, "is eating \xF0\x9F\x8D\x9D");
		pthread_mutex_lock(&ph->args->checker);
		ph->t_lastmeal = timestamp(ph->args);
		ph->meals_eaten += 1;
		pthread_mutex_unlock(&ph->args->checker);
		ft_sleep(ph, ph->args->t_to_eat);
		pthread_mutex_unlock(&ph->args->fork[ph->l_fork]);
		pthread_mutex_unlock(&ph->args->fork[ph->r_fork]);
	}
}

void	ph_think(t_philo *ph)
{
	if (ph->args->game_over == FALSE)
		print(ph, "is thinking \xF0\x9F\x92\xAD");
}

void	ph_sleep(t_philo *ph)
{
	if (ph->args->game_over == FALSE)
	{
		print(ph, "is sleeping \xF0\x9F\x92\xA4");
		ft_sleep(ph, ph->args->t_to_sleep);
	}
}
