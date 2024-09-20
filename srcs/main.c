/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:14:20 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/20 12:41:24 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	main(int ac, char **av)
{
	t_info	info;
	t_map	*map;

	info.map = NULL;
	if (!error_handling(ac, av, &info))
		return (EXIT_FAILURE);
	if (!map_handling(&info, &map))
		return (ft_freeall(&info, &map), EXIT_FAILURE);
	if (close(info.fd) == -1)
		return (ft_freeall(&info, &map), EXIT_FAILURE);
	return (ft_freeall(&info, &map), EXIT_SUCCESS);
}
