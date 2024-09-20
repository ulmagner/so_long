/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:37:27 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/20 23:19:33 by ulysse           ###   ########.fr       */
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

int	check_close_map(t_map **map, t_info *info)
{
	t_map	*curr;

	curr = *map;
	while (curr)
	{
		if (((curr->x == 0 || curr->x == info->nbr_column - 1)
				&& curr->index != '1')
			|| ((curr->y == 0 || curr->y == info->nbr_line - 1)
				&& curr->index != '1'))
			return (0);
		curr = curr->right;
	}
	return (1);
}

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
