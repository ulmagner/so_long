/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:14:20 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/08 21:44:29 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	main(int ac, char **av)
{
	t_solong	solong;

	solong = (t_solong){0};
	if (!error_handling(ac, av, &solong.info))
		return (EXIT_FAILURE);
	if (!get_paths(av[4], &solong.info))
		return (EXIT_FAILURE);
	if (!map_handling(&solong.info, &solong.map, &solong.player, &solong.oeuil))
		return (ft_clearall(&solong), EXIT_FAILURE);
	if (!launcher(&solong, av))
		return (ft_clearall(&solong), EXIT_FAILURE);
	return (ft_clearall(&solong), EXIT_SUCCESS);
}
