/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:40:12 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/16 16:42:53 by ulmagner         ###   ########.fr       */
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
		copy_to_ground(&all->tile[1][0][all->wall.anim], &all->ground, col);
	}
	else if ((col->i == '1' || col->i == 'F') && col->y == all->info.line - 1)
		copy_to_ground(&all->tile[1][1][0], &all->ground, col);
	else if ((col->i == '1' || col->i == 'F') && col->x == 0)
		copy_to_ground(&all->tile[1][2][0], &all->ground, col);
	else if ((col->i == '1' || col->i == 'F') && col->x == all->info.column - 1)
		copy_to_ground(&all->tile[1][3][0], &all->ground, col);
	else if (col->i == '1' || col->i == 'F')
		copy_to_ground(&all->tile[2][0][0], &all->ground, col);
	if (col->i == '1' && col->x == 0 && col->y == 0)
		copy_to_ground(&all->tile[1][4][0], &all->ground, col);
	if (col->i == '1' && col->x == 0 && col->y == all->info.line - 1)
		copy_to_ground(&all->tile[1][4][2], &all->ground, col);
	if (col->i == '1' && col->x == all->info.column - 1 && col->y == 0)
		copy_to_ground(&all->tile[1][4][1], &all->ground, col);
	if (col->i == '1' && col->x == all->info.column - 1 \
		&& col->y == all->info.line - 1)
		copy_to_ground(&all->tile[1][4][3], &all->ground, col);
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
			copy_to_ground(&all->tile[0][0][0], &all->ground, col);
		else
			copy_to_ground(&all->tile[0][0][1], &all->ground, col);
		wall_management(all, col);
		if (col->i == 'E' && all->info.exit)
			copy_to_ground(&all->tile[3][0][0], &all->ground, col);
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
			copy_to_ground(&all->tile[3][0][0], &all->ground, col);
			all->info.exit_x = col->x;
			all->info.exit_y = col->y;
		}
		col = col->right;
	}
}

void	build_minimap(t_all *all, t_image ***tile, t_image *game)
{
	int	i;
	int	mini_x;
	int	mini_y;

	mini_y = tile[8][1][0].h - 40;
	mini_x = tile[8][1][0].w - 46;
	i = -1;
	copy_to_game(&tile[8][1][0], game, 0, 0);
	while (++i < all->info.ennemies && !all->oeil[i].is_dead)
		copy_to_game(&tile[8][2][0], game, \
			(all->oeil[i].x * mini_x / game->w), \
			(all->oeil[i].y * mini_y / game->h));
	i = -1;
	while (++i < all->info.collectible && !all->slime[i].is_free)
		copy_to_game(&tile[8][3][0], game, \
			(all->slime[i].x * mini_x / game->w), \
			(all->slime[i].y * mini_y / game->h));
	copy_to_game(&tile[8][5][0], game, \
		(all->player.x * mini_x / game->w), \
		(all->player.y * mini_y / game->h));
	if (all->info.exit)
		copy_to_game(&tile[8][4][0], game, \
			(all->info.exit_x * mini_x / game->w), \
			(all->info.exit_y * mini_y / game->h));
}
