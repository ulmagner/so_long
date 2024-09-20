/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:37:27 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/20 19:10:56 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	check_ep_doubles(t_info *info)
{
	int	i;
	int	e;
	int	p;

	e = 0;
	p = 0;
	i = -1;
	while (info->map[++i])
	{
		if (info->map[i] == 'E')
			e++;
		if (info->map[i] == 'P')
			p++;
	}
	if (e > 1 || e == 0 || p > 1 || p == 0)
		return (0);
	return (1);
}

// int	check_doubles(t_info *info)
// {
// 	int	j;
// 	int	k;

// 	j = -1;
// 	while (info->map[++j])
// 	{
// 		k = -1;
// 		if (info->map[j] == 'P' || info->map[j] == 'E')
// 		{
// 			while (++k < j)
// 			{
// 				if (info->map[k] == info->map[j])
// 					return (1);
// 			}
// 		}
// 	}
// 	return (0);
// }

int	error_handling(int ac, char **av, t_info *info)
{
	if (ac != 2)
		return (0);
	if (ft_strncmp(av[1] + (ft_strlen(av[1]) - 4), ".ber", 4))
		return (0);
	info->fd = open(av[1], O_RDWR);
	if (info->fd < 0)
		return (ft_printf(2, "Error\nCarte can't be open\n"), 0);
	return (1);
}
