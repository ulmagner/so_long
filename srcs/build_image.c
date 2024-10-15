/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:40:12 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/15 14:15:48 by ulmagner         ###   ########.fr       */
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
		copy_to_ground(&all->tileset[1][0][all->wall.anim], &all->ground, col);
	}
	else if ((col->i == '1' || col->i == 'F') && col->y == all->info.line - 1)
		copy_to_ground(&all->tileset[1][1][0], &all->ground, col);
	else if ((col->i == '1' || col->i == 'F') && col->x == 0)
		copy_to_ground(&all->tileset[1][2][0], &all->ground, col);
	else if ((col->i == '1' || col->i == 'F') && col->x == all->info.column - 1)
		copy_to_ground(&all->tileset[1][3][0], &all->ground, col);
	else if (col->i == '1' || col->i == 'F')
		copy_to_ground(&all->tileset[2][0][0], &all->ground, col);
	if (col->i == '1' && col->x == 0 && col->y == 0)
		copy_to_ground(&all->tileset[1][4][0], &all->ground, col);
	if (col->i == '1' && col->x == 0 && col->y == all->info.line - 1)
		copy_to_ground(&all->tileset[1][4][2], &all->ground, col);
	if (col->i == '1' && col->x == all->info.column - 1 && col->y == 0)
		copy_to_ground(&all->tileset[1][4][1], &all->ground, col);
	if (col->i == '1' && col->x == all->info.column - 1 \
		&& col->y == all->info.line - 1)
		copy_to_ground(&all->tileset[1][4][3], &all->ground, col);
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
			copy_to_ground(&all->tileset[0][0][0], &all->ground, col);
		else
			copy_to_ground(&all->tileset[0][0][1], &all->ground, col);
		wall_management(all, col);
		if (col->i == 'E' && all->info.exit)
			copy_to_ground(&all->tileset[3][0][0], &all->ground, col);
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
			copy_to_ground(&all->tileset[3][0][0], &all->ground, col);
			all->info.exit_x = col->x;
			all->info.exit_y = col->y;
		}
		col = col->right;
	}
}

void	build_minimap(t_all *all, t_image ***tile, t_view *view, t_image *plan)
{
	int	i;
	int	mini_x;
	int	mini_y;

	mini_y = tile[8][1][0].h - 40;
	mini_x = tile[8][1][0].w - 46;
	i = -1;
	copy_to_game(&tile[8][1][0], &all->game, \
		(view->x - view->w / 2), (view->y - view->h / 2));
	while (++i < all->info.ennemies)
		copy_to_game(&tile[8][2][0], &all->game, \
			(view->x - view->w / 2) + (all->oeuil[i].x * mini_x / plan->w), \
			(view->y - view->h / 2) + (all->oeuil[i].y * mini_y / plan->h));
	i = -1;
	while (++i < all->info.collectible)
		copy_to_game(&tile[8][3][0], &all->game, \
			(view->x - view->w / 2) + (all->slime[i].x * mini_x / plan->w), \
			(view->y - view->h / 2) + (all->slime[i].y * mini_y / plan->h));
	copy_to_game(&tile[8][5][0], &all->game, \
		(view->x - view->w / 2) + (all->player.x * mini_x / plan->w), \
		(view->y - view->h / 2) + (all->player.y * mini_y / plan->h));
	if (all->info.exit)
		copy_to_game(&tile[8][4][0], &all->game, \
			(view->x - view->w / 2) + (all->info.exit_x * mini_x / plan->w), \
			(view->y - view->h / 2) + (all->info.exit_y * mini_y / plan->h));
}
