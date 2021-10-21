/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:42:38 by nschumac          #+#    #+#             */
/*   Updated: 2021/09/08 17:25:37 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

typedef enum e_philostates
{
	PS_NONE,
	PS_DEAD,
	PS_SLEEPING,
	PS_EATING,
	PS_THINKING,
	PS_FORK
}				t_philostates;

typedef struct s_data
{
	unsigned long		ttdie;
	unsigned long		tteat;
	unsigned long		ttsleep;
	long long			musteat;
	unsigned long		basetime;
	pthread_mutex_t		*m_p;
	unsigned long		philo_num;
	unsigned long		loaded;
	char				death;
}				t_data;

typedef struct s_philos
{
	t_data			*data;
	t_philostates	state;
	pthread_mutex_t	*m_f1;
	pthread_mutex_t	*m_f2;
	unsigned long	actiontime;
	unsigned long	deathtime;
	long long		eatcount;
	unsigned long	num;
}				t_philos;

unsigned long	ft_atol(char *str);
unsigned long	ft_millsec(void);
char			ft_free(void *ptr);
char			ft_createthreads(unsigned long c,
					t_philos *philosophers, t_data *data);
char			ft_freedata(t_philos *ptr);
void			ft_eating(t_philos *philo);
void			ft_thinking(t_philos *philo);
void			ft_sleeping(t_philos *philo);
void			ft_msg(t_philos *philo);
unsigned long	ft_time(t_philos *philo, t_philostates state);
char			ft_deathhelper(t_philos *philo);
#endif