/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:40:12 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/13 22:49:13 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	wall_management(t_all *all, t_map *col)
{
	if ((col->i == '1' || col->i == 'F') && col->y == 0)
	{
		if (col->x == 0)
			all->wall.anim = 0;
		else
			all->wall.anim = (all->wall.anim + 1) % 3;
		copy_to_map(&all->tileset[1][0][all->wall.anim], &all->ground, col);
	}
	else if ((col->i == '1' || col->i == 'F') && col->y == all->info.line - 1)
		copy_to_map(&all->tileset[1][1][0], &all->ground, col);
	else if ((col->i == '1' || col->i == 'F') && col->x == 0)
		copy_to_map(&all->tileset[1][2][0], &all->ground, col);
	else if ((col->i == '1' || col->i == 'F') && col->x == all->info.column - 1)
		copy_to_map(&all->tileset[1][3][0], &all->ground, col);
	else if (col->i == '1' || col->i == 'F')
		copy_to_map(&all->tileset[2][0][0], &all->ground, col);
	if (col->i == '1' && col->x == 0 && col->y == 0)
		copy_to_map(&all->tileset[1][4][0], &all->ground, col);
	if (col->i == '1' && col->x == 0 && col->y == all->info.line - 1)
		copy_to_map(&all->tileset[1][4][2], &all->ground, col);
	if (col->i == '1' && col->x == all->info.column - 1 && col->y == 0)
		copy_to_map(&all->tileset[1][4][1], &all->ground, col);
	if (col->i == '1' && col->x == all->info.column - 1 \
		&& col->y == all->info.line - 1)
		copy_to_map(&all->tileset[1][4][3], &all->ground, col);
}

void	build_ground(t_all *all)
{
	t_map	*col;
	int		i;

	i = -1;
	col = all->map;
	while (col)
	{
		if (++i % 2 == 0)
			copy_to_map(&all->tileset[0][0][0], &all->ground, col);
		else
			copy_to_map(&all->tileset[0][0][1], &all->ground, col);
		wall_management(all, col);
		if (col->i == 'E' && all->info.exit)
			copy_to_map(&all->tileset[3][0][0], &all->ground, col);
		col = col->right;
	}
}

void	build_plan(t_all *all)
{
	t_map	*col;

	col = all->map;
	while (col)
	{
		if (col->i == 'E' && all->info.exit)
		{
			copy_to_map(&all->tileset[3][0][0], &all->ground, col);
			all->info.exit_x = col->x;
			all->info.exit_y = col->y;
		}
		col = col->right;
	}
}

void	build_game(t_all *all)
{
	int	i;
	int	mini_x;
	int	mini_y;

	mini_y = all->tileset[8][1][0].h - 40;
	mini_x = all->tileset[8][1][0].w - 46;
	i = -1;
	copy_to_game(&all->tileset[8][1][0], &all->game, 0, 0);
	while (++i < all->info.ennemies)
		copy_to_game(&all->tileset[8][2][0], &all->game, \
			((all->oeuil[i].x * mini_x) / all->plan.w), \
			((all->oeuil[i].y * mini_y) / all->plan.h));
	i = -1;
	while (++i < all->info.collectible)
		copy_to_game(&all->tileset[8][3][0], &all->game, \
			((all->slime[i].x * mini_x) / all->plan.w), \
			((all->slime[i].y * mini_y) / all->plan.h));
	copy_to_game(&all->tileset[8][5][0], &all->game, \
		((all->player.x * mini_x) / all->plan.w), \
		((all->player.y * mini_y) / all->plan.h));
	if (all->info.exit)
		copy_to_game(&all->tileset[8][4][0], &all->game, \
			(all->info.exit_x * mini_x / all->plan.w), \
			(all->info.exit_y * mini_y / all->plan.h));
}
