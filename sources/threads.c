/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:42:14 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/21 16:51:01 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

char	ft_freedata(t_philos *ptr)
{
	unsigned long	count;

	count = ptr->data->philo_num;
	pthread_mutex_unlock(ptr->data->m_p);
	pthread_mutex_destroy(ptr->data->m_p);
	while (count)
	{
		pthread_mutex_unlock(ptr[count - 1].m_f1);
		if (ptr[count - 1].m_f1 && !pthread_mutex_destroy(ptr[count - 1].m_f1))
			ft_free(ptr[count - 1].m_f1);
		count--;
	}
	if (ptr->data->philo_num == 1)
	{
		pthread_mutex_unlock(ptr[0].m_f2);
		if (ptr[0].m_f2 && !pthread_mutex_destroy(ptr[0].m_f2))
			ft_free(ptr[0].m_f2);
	}
	free(ptr->data->m_p);
	usleep(1000 * 500);
	free(ptr);
	return (1);
}

static void	*ft_deathroutine(void *arg)
{
	t_philos		*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(philo->data->m_p);
	++philo->data->loaded;
	pthread_mutex_unlock(philo->data->m_p);
	while (1)
	{
		if (philo->data->loaded != philo->data->philo_num + 1)
			continue ;
		usleep(philo->data->philo_num * 15);
		if (ft_deathhelper(philo))
			return (NULL);
	}
	return (NULL);
}

static void	*ft_mainroutine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(philo->data->m_p);
	++philo->data->loaded;
	pthread_mutex_unlock(philo->data->m_p);
	while (philo->data->loaded != philo->data->philo_num + 1)
		usleep(10);
	philo->data->basetime = ft_millsec();
	philo->deathtime = philo->data->basetime;
	philo->actiontime = philo->data->basetime;
	pthread_mutex_lock(philo->data->m_p);
	ft_msg(philo);
	pthread_mutex_unlock(philo->data->m_p);
	while (philo->eatcount != philo->data->musteat && !philo->data->death)
	{
		usleep(50);
		if (philo->state == PS_THINKING)
			ft_thinking(philo);
		else if (philo->state == PS_EATING)
			ft_eating(philo);
		else if (philo->state == PS_SLEEPING)
			ft_sleeping(philo);
	}
	return (arg);
}

void	ft_wait(t_philos	*philos)
{
	unsigned long	yeet;

	while (!philos->data->death)
	{
		yeet = 0;
		while (yeet < philos->data->philo_num)
		{
			if (philos[yeet].eatcount != philos->data->musteat)
				break ;
			yeet++;
			if (yeet == philos->data->philo_num)
				return ;
		}
	}
}

char	ft_createthreads(unsigned long c,
		t_philos *philosophers, t_data *data)
{
	pthread_t		threads;

	if (!philosophers)
		return (1);
	pthread_mutex_init(data->m_p, NULL);
	while (++c && c <= data->philo_num)
	{
		philosophers[c - 1].state = PS_THINKING;
		if ((c % 2) == 1)
			philosophers[c - 1].state = PS_SLEEPING;
		if (data->philo_num == 1)
			pthread_mutex_lock(philosophers[c - 1].m_f2);
		if (pthread_create(&threads, NULL,
				&ft_mainroutine, (void *)&philosophers[c - 1]))
			return (ft_freedata(philosophers));
		pthread_detach(threads);
	}
	if (pthread_create(&threads, NULL,
			&ft_deathroutine, (void *)&philosophers[0]))
		return (ft_freedata(philosophers));
	pthread_detach(threads);
	ft_wait(philosophers);
	ft_freedata(philosophers);
	return (0);
}
