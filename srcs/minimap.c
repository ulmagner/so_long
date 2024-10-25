/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:28:13 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/24 14:28:49 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	build_minimap(t_all *all, t_image ***tile, t_image *game)
{
	int	i;

	int (j) = -1;
	int (mini_x) = tile[8][1][0].w - 46;
	int (mini_y) = tile[8][1][0].h - 40;
	copy_to_game(&tile[8][1][0], game, 0, 0);
	while (++j < all->info.oeil)
	{
		i = -1;
		while (++i < all->info.ennemies && !all->oeil[j][i].is_dead)
			copy_to_game(&tile[8][2][0], game, \
				(all->oeil[j][i].x * mini_x / game->w), \
				(all->oeil[j][i].y * mini_y / game->h));
	}
	i = -1;
	while (++i < all->info.collectible && !all->slime[i].is_free)
		copy_to_game(&tile[8][3][0], game, (all->slime[i].x * mini_x / game->w),
			(all->slime[i].y * mini_y / game->h));
	copy_to_game(&tile[8][5][0], game, \
		(all->player.x * mini_x / game->w), (all->player.y * mini_y / game->h));
	if (all->info.exit)
		copy_to_game(&tile[8][4][0], game, \
			(all->info.exit_x * mini_x / game->w), \
			(all->info.exit_y * mini_y / game->h));
}
