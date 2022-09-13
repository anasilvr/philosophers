/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:48:42 by anarodri          #+#    #+#             */
/*   Updated: 2022/09/13 14:37:14 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_control	data;

	if (check_argv(argc, argv) != 0)
		return (-1);
	data = init_s_control(argv);
	if (data.error != 0)
		return (-1);
	else
		philo_start(&data);
	return (0);
}
