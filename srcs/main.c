/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:14:20 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 19:46:39 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

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
