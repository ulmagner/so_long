/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:37:27 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/27 10:36:18 by ulmagner         ###   ########.fr       */
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
		if (info->map[i] == 'C')
			info->coin++;
	}
	if (e > 1 || e == 0 || p > 1 || p == 0)
		return (0);
	return (1);
}

void	floodfill(t_map *player, int *c, int *e)
{
	if (player->index == 'C')
		(*c)++;
	if (player->index == 'E')
		(*e)++;
	player->is_visited = 1;
	if (player->right->index != '1' && player->right != NULL
		&& !player->right->is_visited)
		floodfill(player->right, c, e);
	if (player->left->index != '1' && player->left != NULL
		&& !player->left->is_visited)
		floodfill(player->left, c, e);
	if (player->up->index != '1' && player->up != NULL
		&& !player->up->is_visited)
		floodfill(player->up, c, e);
	if (player->down->index != '1' && player->down != NULL
		&& !player->down->is_visited)
		floodfill(player->down, c, e);
}

int	check_close_map(t_map **map, t_info *info, t_player **player)
{
	t_map	*curr;
	int		c;
	int		e;

	c = 0;
	e = 0;
	curr = *map;
	while (curr)
	{
		if (((curr->x == 0 || curr->x == info->nbr_column - 1)
				&& curr->index != '1')
			|| ((curr->y == 0 || curr->y == info->nbr_line - 1)
				&& curr->index != '1'))
			return (0);
		if (curr->index == 'P')
		{
			(*player)->x = curr->x * 64;
			(*player)->y = curr->y * 64;
			(*player)->hero = curr;
			floodfill(curr, &c, &e);
		}
		curr = curr->right;
	}
	if (c != info->coin || !e)
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
		return (ft_printf(2, "Error\nCarte can't be open\n"), 0);
	return (1);
}
