/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschumac <nschumac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:42:18 by nschumac          #+#    #+#             */
/*   Updated: 2021/10/21 16:50:55 by nschumac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static char	ft_checkinputs(int argc, char *argv[])
{
	int	c;

	while (--argc)
	{
		c = 0;
		while (argv[argc][c])
		{
			if (argv[argc][c] < '0' || argv[argc][c] > '9')
				return (0);
			c++;
		}
	}
	return (1);
}

t_data	*ft_createdata(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(t_data));
	data->musteat = -1;
	if (argc == 6)
		data->musteat = ft_atol(argv[--argc]);
	data->ttsleep = ft_atol(argv[--argc]);
	data->tteat = ft_atol(argv[--argc]);
	data->ttdie = ft_atol(argv[--argc]);
	data->philo_num = ft_atol(argv[--argc]);
	data->loaded = 0;
	if (data->philo_num == 0 && ft_free(data))
		return (NULL);
	data->m_p = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!data->m_p && ft_free(data))
		return (NULL);
	return (data);
}

static void	*ft_calloc(unsigned long size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		return (NULL);
	memset(ret, 0, size);
	return (ret);
}

t_philos	*ft_createphilosophers(t_philos *ret,
			unsigned long count, t_data *data)
{
	ret = ft_calloc(sizeof(t_philos) * data->philo_num);
	while (ret != NULL && ++count && count <= data->philo_num)
	{
		ret[count - 1].num = count;
		ret[count - 1].data = data;
		if (count == data->philo_num && data->philo_num > 1)
			ret[count - 1].m_f2 = ret[0].m_f1;
		else
		{
			ret[count - 1].m_f2 = malloc(sizeof(pthread_mutex_t));
			if (!ret[count - 1].m_f2 && ft_freedata(ret))
				return (0);
			pthread_mutex_init(ret[count - 1].m_f2, NULL);
		}
		if (count == 1)
		{
			ret[count - 1].m_f1 = malloc(sizeof(pthread_mutex_t));
			if (!ret[count - 1].m_f1 && ft_freedata(ret))
				return (0);
			pthread_mutex_init(ret[count - 1].m_f1, NULL);
		}
		else
			ret[count - 1].m_f1 = ret[count - 2].m_f2;
	}
	return (ret);
}

int	main(int argc, char *argv[])
{
	t_data		*data;
	t_philos	*philosophers;

	if (argc != 5 && argc != 6)
	{
		write(2, "Error: Invalid Argument Amount\n", 32);
		return (1);
	}
	if (!ft_checkinputs(argc, argv))
	{
		write(2, "Error: Invalid Argument Types\n", 31);
		return (1);
	}
	data = ft_createdata(argc, argv);
	if (!data)
		return (1);
	philosophers = ft_createphilosophers(0, 0, data);
	return (ft_createthreads(0, philosophers, data));
}
