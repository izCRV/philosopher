/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aizsak <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 08:19:03 by aizsak            #+#    #+#             */
/*   Updated: 2023/02/12 08:23:43 by aizsak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write(t_philo *philo, int what_message)
{
	pthread_mutex_lock(&philo->data_ptr->write);
	if (!ft_check_die(philo) && !ft_check_max_eat(philo - (philo->id - 1)))
	{
		if (what_message == THINK)
			printf("%ld - Philosophers %d is thinking\n", \
			ft_get_time() - philo->data_ptr->time, philo->id);
		else if (what_message == SLEEP)
			printf("%ld - Philosophers %d is sleeping\n", \
			ft_get_time() - philo->data_ptr->time, philo->id);
		else if (what_message == EAT)
			printf("%ld - Philosophers %d is eating\n", \
			ft_get_time() - philo->data_ptr->time, philo->id);
		else if (what_message == LOCK_FORK)
			printf("%ld - Philosophers %d has taken a fork\n", \
			ft_get_time() - philo->data_ptr->time, philo->id);
	}
	else if (what_message == DIE && !ft_check_max_eat(philo - (philo->id - 1)))
		printf("%ld - Philosophers %d died\n", \
		ft_get_time() - philo->data_ptr->time, philo->id);
	pthread_mutex_unlock(&philo->data_ptr->write);
}

void	ft_think(t_philo *philo)
{
	if (!ft_check_die(philo))
		ft_write(philo, THINK);
}

void	ft_sleep(t_philo *philo, long long tts)
{
	if (!ft_check_die(philo))
	{
		ft_write(philo, SLEEP);
		ft_usleep(philo, tts);
	}
}

void	ft_eat(t_philo *philo)
{
	if (!ft_check_die(philo))
	{
		ft_lock_fork(philo);
		pthread_mutex_lock(&philo->data_ptr->check_last_eat);
		philo->last_eat = ft_get_time() - philo->data_ptr->time;
		pthread_mutex_unlock(&philo->data_ptr->check_last_eat);
		ft_write(philo, EAT);
		pthread_mutex_lock(&philo->data_ptr->check_max_eat);
		philo->nb_meal++;
		pthread_mutex_unlock(&philo->data_ptr->check_max_eat);
		ft_usleep(philo, philo->data_ptr->tte * 1000);
		ft_unlock_fork(philo);
	}
}
