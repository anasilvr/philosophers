/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:48:42 by anarodri          #+#    #+#             */
/*   Updated: 2023/04/04 09:45:50 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_control	*data;

	if (check_argv(argc, argv) != 0)
		return (-1);
	data = (t_control *)ft_calloc(1, sizeof(t_control));
	if (!data)
		return (-1);
	init_s_control(argv, data);
	philo_start(data);
	philo_end(data);
	return (0);
}
