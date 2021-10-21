/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:42:08 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/21 16:50:42 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned long	ft_atol(char *str)
{
	unsigned long long	buf;

	buf = 0;
	while (*str)
	{
		buf *= 10;
		buf += *str - '0';
		str++;
	}
	return (buf);
}

unsigned long	ft_strlen(const char *str)
{
	unsigned long	length;

	length = 0;
	while (str[length] != 0)
		length++;
	return (length);
}

char	ft_deathhelper(t_philos *philo)
{
	unsigned long	c;

	c = 0;
	while (++c <= philo->data->philo_num)
	{
		if (ft_time(&philo[c - 1], PS_DEAD)
			&& philo->eatcount != philo->data->musteat)
		{
			pthread_mutex_lock(philo->data->m_p);
			philo[c - 1].state = PS_DEAD;
			ft_msg(&philo[c - 1]);
			philo->data->death = 1;
			return (1);
		}
	}
	return (0);
}

unsigned long	ft_millsec(void)
{
	struct timeval	tval;

	gettimeofday(&tval, NULL);
	return (tval.tv_sec * 1000 + tval.tv_usec / 1000);
}

char	ft_free(void *ptr)
{
	free(ptr);
	return (1);
}
