/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:37:27 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/18 20:06:38 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	error_handling(int ac, char **av, t_info *info, int	lvl)
{
	if (ac < 3)
		return (0);
	if (ft_strncmp(av[lvl] + (ft_strlen(av[lvl]) - 4), ".ber", 4))
		return (0);
	info->fd = open(av[lvl], O_RDWR);
	if (info->fd < 0)
		return (ft_printf(2, "Error\nplan can't be open\n"), 0);
	return (1);
}
