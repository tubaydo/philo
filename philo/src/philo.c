/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taydogan <taydogan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:37:02 by taydogan          #+#    #+#             */
/*   Updated: 2023/09/14 13:37:04 by taydogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_philo_must_eat(t_philo *philo)
{
	if (philo->info->must_eat > 0 && ++philo->num_eat == philo->info->must_eat)
	{
		if (++philo->info->finished_philos == philo->info->num_philos)
		{
			philo->info->end = 1;
			pthread_mutex_lock(&philo->info->mtx_end);
		}
	}
}

void	philo_eat(t_philo *philo)
{
	while (1)
	{
		if (philo->info->fork_status[philo->r_fork] == FREE)
		{
			pthread_mutex_lock(&philo->info->forks[philo->r_fork]);
			philo->info->fork_status[philo->r_fork] = LOCK;
			print_philo_status(philo, "has taken a fork");
			pthread_mutex_lock(&philo->info->forks[philo->l_fork]);
			philo->info->fork_status[philo->l_fork] = LOCK;
			print_philo_status(philo, "has taken a fork");
			philo->last_eat = get_useconds();
			print_philo_status(philo, "is eating");
			check_philo_must_eat(philo);
			ft_usleep((philo->info->time_to_eat * 1000));
			philo->info->fork_status[philo->r_fork] = FREE;
			philo->info->fork_status[philo->l_fork] = FREE;
			pthread_mutex_unlock(&philo->info->forks[philo->r_fork]);
			pthread_mutex_unlock(&philo->info->forks[philo->l_fork]);
			break ;
		}
		else
			usleep(100);
	}
}

void	philo_sleep(t_philo *philo)
{
	print_philo_status(philo, "is sleeping");
	ft_usleep((philo->info->time_to_sleep * 1000));
}

void	philo_think(t_philo *philo)
{
	print_philo_status(philo, "is thinking");
}

void	*philo_life(void *arg)
{
	while (1)
	{
		philo_eat((t_philo *)arg);
		philo_sleep((t_philo *)arg);
		philo_think((t_philo *)arg);
	}
	return (NULL);
}
