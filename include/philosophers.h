/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:49:36 by anarodri          #+#    #+#             */
/*   Updated: 2022/09/14 13:18:04 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

# define RED "\e[0;31m"
# define RESET "\e[0m"

# define FALSE	0
# define TRUE	1
# define ERR_CMD "Command line error. Ex.: ./philo [nb_de_philo] [time_to_die] [time_to_eat]\
 [time_to_sleep] [nb_time_must_eat] (P.s.: [nb_time_must_eat] is optional.)\n"
# define ERR_MAX "Invalid number of philosophers. Máx.: 200\n"
# define ERR_ARGS "All arguments must be set as greater than zero integers.\n"

typedef struct s_control	t_control;
typedef struct s_philo		t_philo;

typedef struct s_philo
{
	pthread_t	tid;
	int			id;
	int			meals_eaten;
	long long	t_lastmeal;
	int			l_fork;
	int			r_fork;
	t_control	*args;
}	t_philo;

typedef struct s_control
{
	int				nb_philo;
	long long		t0;
	long long		t_to_die;
	long long		t_to_eat;
	long long		t_to_sleep;
	int				max_meals;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	cout;
	pthread_mutex_t	checker;
	int				error;
	int				end_meal;
	int				game_over;
}	t_control;

/* init.c */
int			check_argv(int argc, char **argv);
void	init_s_control(char **argv, t_control *input);
void		init_mutexes(t_control *input);
void		init_s_philo(t_control *input);

/* timeutils.c */
long long	start_time(void);
long long	timestamp(t_control *input);
void		ft_sleep(t_philo *p, int t_wait);

/* utils.c */
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t num, size_t size);
void		print(t_philo *p, char *state);

/* philocontrol.c */
void		philo_start(t_control *input);
void		*philo_do(void *p);
void		philo_end(t_control *input);
void		checker(t_control *c);
void		check_death(t_control *c);

/* philoacts.c */
void		ph_eat(t_philo *ph);
void		ph_think(t_philo *ph);
void		ph_sleep(t_philo *ph);

#endif