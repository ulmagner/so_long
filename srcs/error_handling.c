/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:37:27 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/15 14:26:21 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	check_ep_doubles(t_info *info)
{
	int	i;
	int	e;
	int	p;
	int	o;

	e = 0;
	o = 0;
	p = 0;
	i = -1;
	while (info->map[++i])
	{
		if (info->map[i] == 'E')
			e++;
		if (info->map[i] == 'P')
			p++;
		if (info->map[i] == 'C')
			info->coin++;
		if (info->map[i] == 'F')
			info->trap++;
		if (info->map[i] == 'O')
			info->ennemies++;
	}
	if (e > 1 || !e || p > 1 || !p)
		return (0);
	return (1);
}

int	error_handling(int ac, char **av, t_info *info)
{
	if (ac < 5)
		return (0);
	if (ft_strncmp(av[1] + (ft_strlen(av[1]) - 4), ".ber", 4))
		return (0);
	info->fd = open(av[1], O_RDWR);
	if (info->fd < 0)
		return (ft_printf(2, "Error\nplan can't be open\n"), 0);
	return (1);
}
