/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 09:57:02 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/03 09:57:29 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	dir_up(t_player *player, t_movement *movement, t_solong *solong)
{
	if (movement->move[XK_w] && (player->hero->up->index != '1' \
		&& player->y >= player->hero->up->y_pxl))
	{
		ft_memset(movement->index_move, 0, sizeof(movement->index_move));
		movement->index_move[0] = true;
		player->index = 0;
		if (solong->i % player->ms == 0)
		{
			if ((player->animation[0] + 1) % 6 == 0)
				player->animation[0] += 2;
			player->animation[0] = (player->animation[0] + 1) % 6;
		}
		player->y -= player->ms;
		if (player->y <= player->hero->up->y_pxl)
		{
			ft_printf(2, "up\n");
			player->hero = player->hero->up;
		}
	}
}

void	dir_down(t_player *player, t_movement *movement, t_solong *solong)
{
	if (movement->move[XK_s] && player->hero->down->index != '1' \
		&& player->y <= player->hero->down->y_pxl)
	{
		ft_memset(movement->index_move, 0, sizeof(movement->index_move));
		movement->index_move[1] = true;
		player->index = 1;
		if (solong->i % player->ms == 0)
		{
			if ((player->animation[1] + 1) % 6 == 0)
				player->animation[1] += 2;
			player->animation[1] = (player->animation[1] + 1) % 6;
		}
		player->y += player->ms;
		if (player->y >= player->hero->down->y_pxl)
		{
			ft_printf(2, "down\n");
			player->hero = player->hero->down;
		}
	}
}

void	dir_left(t_player *player, t_movement *movement, t_solong *solong)
{
	if (movement->move[XK_a] && player->hero->left->index != '1' \
		&& player->x >= player->hero->left->x_pxl)
	{
		ft_memset(movement->index_move, 0, sizeof(movement->index_move));
		movement->index_move[2] = true;
		player->index = 2;
		if (solong->i % player->ms == 0)
		{
			if ((player->animation[2] + 1) % 6 == 0)
				player->animation[2] += 2;
			player->animation[2] = (player->animation[2] + 1) % 6;
		}
		player->x -= player->ms;
		if (player->x <= player->hero->left->x_pxl)
		{
			ft_printf(2, "left\n");
			player->hero = player->hero->left;
		}
	}
}

void	dir_right(t_player *player, t_movement *movement, t_solong *solong)
{
	if (movement->move[XK_d] && player->hero->right->index != '1' \
		&& player->x <= player->hero->right->x_pxl)
	{
		ft_memset(movement->index_move, 0, sizeof(movement->index_move));
		movement->index_move[3] = 1;
		player->index = 3;
		if (solong->i % player->ms == 0)
		{
			if ((player->animation[3] + 1) % 6 == 0)
				player->animation[3] += 2;
			player->animation[3] = (player->animation[3] + 1) % 6;
		}
		player->x += player->ms;
		if (player->x >= player->hero->right->x_pxl)
		{
			ft_printf(2, "right\n");
			player->hero = player->hero->right;
		}
	}
}
