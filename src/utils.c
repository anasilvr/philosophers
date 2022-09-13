/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:09:59 by anarodri          #+#    #+#             */
/*   Updated: 2022/09/13 14:55:39 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi(const char *str)
{
	long	nbr;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	nbr = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + str[i] - '0';
		i++;
		if (nbr * sign > INT_MAX)
			return (-1);
		if (nbr * sign < INT_MIN)
			return (-1);
	}
	return (nbr * sign);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp;
	size_t			i;

	tmp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		tmp[i] = 0;
		i++;
	}
	s = tmp;
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	ptr = malloc(num * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, (num * size));
	return (ptr);
}

void	print(t_philo *p, char *state)
{
	if (p->args->game_over != TRUE)
	{
		pthread_mutex_lock(&p->args->cout);
		printf("%lld %d %s\n", timestamp(p->args), p->id, state);
		pthread_mutex_unlock(&p->args->cout);
	}
}
