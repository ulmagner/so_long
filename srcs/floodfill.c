/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:25:55 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/16 16:13:39 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	floodfill(t_map *player, int *c, int *e, t_all *all)
{
	if (((player->x == 0 || player->x == all->info.column - 1)
			&& (player->i != '1' && player->i != 'F'))
		|| ((player->y == 0 || player->y == all->info.line - 1)
			&& (player->i != '1' && player->i != 'F')))
		exit(((ft_clearall(all)), EXIT_FAILURE));
	if (player->i == 'C')
		(*c)++;
	if (player->i == 'E')
		(*e)++;
	player->is_visited = 1;
	if ((player->right->i != '1' && player->right->i != 'F') \
		&& player->right != NULL && !player->right->is_visited)
		floodfill(player->right, c, e, all);
	if ((player->left->i != '1' && player->left->i != 'F') \
		&& player->left != NULL && !player->left->is_visited)
		floodfill(player->left, c, e, all);
	if ((player->up->i != '1' && player->up->i != 'F') \
		&& player->up != NULL && !player->up->is_visited)
		floodfill(player->up, c, e, all);
	if ((player->down->i != '1' && player->down->i != 'F') \
		&& player->down != NULL && !player->down->is_visited)
		floodfill(player->down, c, e, all);
}

static void	get_c_p_info(t_map *curr, t_all *all)
{
	if (curr->i == 'C')
	{
		all->slime[all->info.slime].x = curr->x * 64;
		all->slime[all->info.slime].frameslime = 0;
		all->slime[all->info.slime].y = curr->y * 64;
		all->slime[all->info.slime++].r = 11.0;
	}
	if (curr->i == 'F')
	{
		all->trap[all->info.fire].x = curr->x * 64;
		all->trap[all->info.fire].frametrap = 0;
		all->trap[all->info.fire].y = curr->y * 64;
		all->trap[all->info.fire++].r = 64.0;
	}
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
		floodfill(curr, c, e, all);
	}
	if (curr->i == 'O')
	{
		while (++i < all->info.ennemies)
		{
			all->oeil[all->info.o][i].x = curr->x * 64;
			all->oeil[all->info.o][i].y = curr->y * 64;
			all->oeil[all->info.o][i].r = 18.0;
			all->oeil[all->info.o][i].reach = 100.0;
			all->oeil[all->info.o][i].frameoeil = 0;
			all->oeil[all->info.o][i].frameoeill = 0;
		}
		all->info.o++;
	}
	get_c_p_info(curr, all);
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
		start_floodfill(curr, all, &c, &e);
		curr = curr->right;
	}
	if (c != info->coin || !e)
		return (0);
	return (1);
}
