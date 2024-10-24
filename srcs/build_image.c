/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:40:12 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/24 14:38:49 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	corner(t_map *col, t_all *all)
{
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

static void	wall_management(t_all *all, t_map *col, int i)
{
	if (col->y == 0 && (col->x > 0 && col->x < all->info.column - 1))
	{
		if (col->x == 0)
			all->wall.anim = 0;
		else
			all->wall.anim = (all->wall.anim + 1) % 3;
		copy_to_ground(&all->tile[1][0][all->wall.anim], &all->ground, col);
	}
	else if (col->y == all->info.line - 1
		&& (col->x > 0 && col->x < all->info.column - 1))
		copy_to_ground(&all->tile[1][1][0], &all->ground, col);
	else if (col->x == 0 && (col->y > 0 && col->y < all->info.line - 1))
		copy_to_ground(&all->tile[1][2][0], &all->ground, col);
	else if (col->x == all->info.column - 1
		&& (col->y > 0 && col->y < all->info.line - 1))
		copy_to_ground(&all->tile[1][3][0], &all->ground, col);
	else
	{
		if (i % 2 == 0)
			copy_to_ground(&all->tile[2][0][0], &all->ground, col);
		else
			copy_to_ground(&all->tile[2][0][1], &all->ground, col);
	}
	corner(col, all);
}

void	build_ground(t_all *all)
{
	t_map	*col;

	int (i) = -1;
	col = all->map;
	while (col)
	{
		if ((col->y > 0 && col->y < all->info.line - 1)
			&& (col->x > 0 && col->x < all->info.column - 1))
		{
			i++;
			if (i % 4 == 0)
				copy_to_ground(&all->tile[0][0][0], &all->ground, col);
			else if (i % 6 == 0)
				copy_to_ground(&all->tile[0][0][2], &all->ground, col);
			else if (i % 15 == 0)
				copy_to_ground(&all->tile[0][0][3], &all->ground, col);
			else
				copy_to_ground(&all->tile[0][0][1], &all->ground, col);
		}
		if ((col->i == '1' || col->i == 'F'))
			wall_management(all, col, i);
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
