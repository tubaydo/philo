/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taydogan <taydogan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:36:58 by taydogan          #+#    #+#             */
/*   Updated: 2023/09/14 13:37:00 by taydogan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philos(pthread_t *threads, t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->num_philos)
	{
		if (pthread_create(&threads[i], NULL, philo_life, &philo[i]))
		{
			write(2, "Pthread create error\n", 22);
			return (1);
		}
		usleep(50);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_info		*info;
	pthread_t	*threads;

	info = malloc(sizeof(t_info));
	if (!info || !save_args(argc, argv, info) || init_info(info))
		return (1);
	philo = init_philo(info);
	threads = malloc(info->num_philos * sizeof(pthread_t));
	if (!philo || !threads || start_philos(threads, info, philo))
		return (1);
	check_philos_death(philo, info);
	kill_philos(threads, info, philo);
	return (0);
}
