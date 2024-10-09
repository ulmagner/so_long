/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 09:57:02 by ulysse            #+#    #+#             */
/*   Updated: 2024/10/09 19:46:39 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	dir_up(t_player *player, t_movement *movement, t_all *all)
{
	if (movement->move[XK_w] && (player->h->up->i != '1' \
		&& player->h->up->i != 'F') \
		&& player->y >= player->h->up->y_pxl)
	{
		ft_memset(movement->i_move, 0, sizeof(movement->i_move));
		movement->i_move[0] = true;
		player->i = 0;
		if (all->i % 10000 == 0)
		{
			if ((player->animation[0] + 1) % 6 == 0)
				player->animation[0] += 2;
			player->animation[0] = (player->animation[0] + 1) % 6;
		}
		player->y -= player->ms;
		if (player->y <= player->h->up->y_pxl)
		{
			ft_printf(2, "up: [x:y] [%d %d] pxl\n", player->x, player->y);
			player->h = player->h->up;
		}
	}
}

void	dir_down(t_player *player, t_movement *movement, t_all *all)
{
	if (movement->move[XK_s] && (player->h->down->i != '1' \
		&& player->h->down->i != 'F') \
		&& player->y <= player->h->down->y_pxl)
	{
		ft_memset(movement->i_move, 0, sizeof(movement->i_move));
		movement->i_move[1] = true;
		player->i = 1;
		if (all->i % 10000 == 0)
		{
			if ((player->animation[1] + 1) % 6 == 0)
				player->animation[1] += 2;
			player->animation[1] = (player->animation[1] + 1) % 6;
		}
		player->y += player->ms;
		if (player->y >= player->h->down->y_pxl)
		{
			ft_printf(2, "down: [x:y] [%d %d] pxl\n", player->x, player->y);
			player->h = player->h->down;
		}
	}
}

void	dir_left(t_player *player, t_movement *movement, t_all *all)
{
	if (movement->move[XK_a] && (player->h->left->i != '1' \
		&& player->h->left->i != 'F') \
		&& player->x >= player->h->left->x_pxl)
	{
		ft_memset(movement->i_move, 0, sizeof(movement->i_move));
		movement->i_move[2] = true;
		player->i = 2;
		if (all->i % 10000 == 0)
		{
			if ((player->animation[2] + 1) % 6 == 0)
				player->animation[2] += 2;
			player->animation[2] = (player->animation[2] + 1) % 6;
		}
		player->x -= player->ms;
		if (player->x <= player->h->left->x_pxl)
		{
			ft_printf(2, "left: [x:y] [%d %d] pxl\n", player->x, player->y);
			player->h = player->h->left;
		}
	}
}

void	dir_right(t_player *player, t_movement *movement, t_all *all)
{
	if (movement->move[XK_d] && (player->h->right->i != '1' \
		&& player->h->right->i != 'F') \
		&& player->x <= player->h->right->x_pxl)
	{
		ft_memset(movement->i_move, 0, sizeof(movement->i_move));
		movement->i_move[3] = 1;
		player->i = 3;
		if (all->i % 10000 == 0)
		{
			if ((player->animation[3] + 1) % 6 == 0)
				player->animation[3] += 2;
			player->animation[3] = (player->animation[3] + 1) % 6;
		}
		player->x += player->ms;
		if (player->x >= player->h->right->x_pxl)
		{
			ft_printf(2, "right: [x:y] [%d %d] pxl\n", player->x, player->y);
			player->h = player->h->right;
		}
	}
}
