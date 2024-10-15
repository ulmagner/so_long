/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:14:20 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/15 11:38:58 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	get_randoms(int min, int max, int count)
{
	int	i;
	int	rd_num;

	i = -1;
	rd_num = -1;
	while (++i < count)
		rd_num = rand() % (max - min + 1) + min;
	return (rd_num);
}

int	main(int ac, char **av)
{
	t_all	all;

	all = (t_all){0};
	if (!error_handling(ac, av, &all.info))
		return (EXIT_FAILURE);
	if (!get_paths(av[4], &all.info))
		return (EXIT_FAILURE);
	if (!map_handling(&all.info, &all.map, &all.player, &all))
		return (ft_clearall(&all), EXIT_FAILURE);
	if (!launcher(&all, av))
		return (ft_clearall(&all), EXIT_FAILURE);
	return (ft_clearall(&all), EXIT_SUCCESS);
}
