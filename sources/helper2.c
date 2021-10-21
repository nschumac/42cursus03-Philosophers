/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:42:22 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/21 16:50:45 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned long	ft_time(t_philos *philo, t_philostates state)
{
	if (state == PS_DEAD)
		return (ft_millsec() - philo->deathtime
			>= philo->data->ttdie);
	if (state == PS_EATING)
		return (ft_millsec() - philo->actiontime
			>= philo->data->tteat);
	if (state == PS_SLEEPING)
		return (ft_millsec() - philo->actiontime
			>= philo->data->ttsleep);
	return (0);
}

void	ft_eating(t_philos *philo)
{
	if (ft_time(philo, philo->state))
	{
		pthread_mutex_unlock(philo->m_f1);
		pthread_mutex_unlock(philo->m_f2);
		++philo->eatcount;
		philo->actiontime = ft_millsec();
		philo->deathtime = ft_millsec();
		philo->state = PS_SLEEPING;
		pthread_mutex_lock(philo->data->m_p);
		ft_msg(philo);
		pthread_mutex_unlock(philo->data->m_p);
	}
}

void	ft_sleeping(t_philos *philo)
{
	if (ft_time(philo, philo->state))
	{
		philo->state = PS_THINKING;
		pthread_mutex_lock(philo->data->m_p);
		ft_msg(philo);
		pthread_mutex_unlock(philo->data->m_p);
	}
}

void	ft_thinking(t_philos *philo)
{
	pthread_mutex_lock(philo->m_f1);
	philo->state = PS_FORK;
	pthread_mutex_lock(philo->data->m_p);
	ft_msg(philo);
	pthread_mutex_unlock(philo->data->m_p);
	pthread_mutex_lock(philo->m_f2);
	pthread_mutex_lock(philo->data->m_p);
	ft_msg(philo);
	pthread_mutex_unlock(philo->data->m_p);
	philo->state = PS_EATING;
	philo->actiontime = ft_millsec();
	pthread_mutex_lock(philo->data->m_p);
	ft_msg(philo);
	pthread_mutex_unlock(philo->data->m_p);
}

void	ft_msg(t_philos *philo)
{
	if (philo->data->death)
		return ;
	if (philo->state == PS_DEAD)
		printf("%lu %lu %s\n",
			ft_millsec() - philo->data->basetime,
			philo->num, "died");
	else if (philo->state == PS_EATING)
		printf("%lu %lu %s\n",
			ft_millsec() - philo->data->basetime,
			philo->num, "is eating");
	else if (philo->state == PS_SLEEPING)
		printf("%lu %lu %s\n",
			ft_millsec() - philo->data->basetime,
			philo->num, "is sleeping");
	else if (philo->state == PS_THINKING)
		printf("%lu %lu %s\n",
			ft_millsec() - philo->data->basetime,
			philo->num, "is thinking");
	else if (philo->state == PS_FORK)
		printf("%lu %lu %s\n",
			ft_millsec() - philo->data->basetime,
			philo->num, "has taken a fork");
}
