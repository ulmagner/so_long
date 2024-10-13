/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:37:27 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/13 22:49:13 by ulmagner         ###   ########.fr       */
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

void	floodfill(t_map *player, int *c, int *e, t_info *info)
{
	if (player->i == 'C')
	{
		info->deco[*c][0] = player->x_pxl;
		info->deco[*c][1] = player->y_pxl;
		(*c)++;
	}
	if (player->i == 'E')
		(*e)++;
	player->is_visited = 1;
	if ((player->right->i != '1' && player->right->i != 'F') \
		&& player->right != NULL && !player->right->is_visited)
		floodfill(player->right, c, e, info);
	if ((player->left->i != '1' && player->left->i != 'F') \
		&& player->left != NULL && !player->left->is_visited)
		floodfill(player->left, c, e, info);
	if ((player->up->i != '1' && player->up->i != 'F') \
		&& player->up != NULL && !player->up->is_visited)
		floodfill(player->up, c, e, info);
	if ((player->down->i != '1' && player->down->i != 'F') \
		&& player->down != NULL && !player->down->is_visited)
		floodfill(player->down, c, e, info);
}

int	start_floodfill(t_map *curr, t_all *all, int *c, int *e)
{
	int	i;

	i = -1;
	if (curr->i == 'P')
	{
		all->player.x = curr->x * 64;
		all->player.y = curr->y * 64;
		all->player.r = 31.0;
		floodfill(curr, c, e, &all->info);
	}
	if (curr->i == 'O')
	{
		while (++i < all->info.ennemies)
		{
			all->oeuil[i].x = curr->x * 64;
			all->oeuil[i].y = curr->y * 64;
			all->oeuil[i].r = 18.0;
		}
	}
	if (curr->i == 'C')
	{
		all->slime[all->info.slime].x = curr->x * 64;
		all->slime[all->info.slime].y = curr->y * 64;
		all->slime[all->info.slime++].r = 11.0;
	}
	if (curr->i == 'F')
	{
		all->trap[all->info.fire].x = curr->x * 64;
		all->trap[all->info.fire].y = curr->y * 64;
		all->trap[all->info.fire++].r = 64.0;
	}
	return (1);
}

int	check_close_map(t_map **map, t_info *info, t_all *all)
{
	t_map	*curr;
	int		c;
	int		e;

	c = 0;
	e = 0;
	curr = *map;
	while (curr)
	{
		if (((curr->x == 0 || curr->x == info->column - 1)
				&& (curr->i != '1' && curr->i != 'F'))
			|| ((curr->y == 0 || curr->y == info->line - 1)
				&& (curr->i != '1' && curr->i != 'F')))
			return (0);
		start_floodfill(curr, all, &c, &e);
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
		return (ft_printf(2, "Error\nplan can't be open\n"), 0);
	return (1);
}
