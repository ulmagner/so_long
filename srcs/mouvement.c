/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:40:44 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/02 16:31:46 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	movement_p(int keycode, t_solong *solong)
{
	solong->movement.move[keycode] = true;
	if (keycode == XK_Escape)
		exit((ft_clearall(solong), EXIT_SUCCESS));
	return (0);
}

int	movement_r(int keycode, t_solong *solong)
{
	solong->movement.move[keycode] = false;
	return (0);
}

int	check_mouvment(t_solong *solong, t_map **player)
{
	t_map	*curr;

	curr = solong->map;
	while (curr)
	{
		if (curr->x_pxl == (*player)->x_pxl && curr->y_pxl == (*player)->y_pxl && curr->index != '1')
			return (1);
		curr = curr->right;
	}
	return (0);
}

int	movement_handling(t_solong *solong, t_player *player)
{
	if (solong->i % 10 != 0)
		return (0);
	player->ms = 8;
	if (solong->movement.move[XK_w] && (player->hero->up->index != '1' && player->y >= player->hero->up->y_pxl))
	{
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
	if (solong->movement.move[XK_s] && player->hero->down->index != '1' && player->y <= player->hero->down->y_pxl)
	{
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
	if (solong->movement.move[XK_a] && player->hero->left->index != '1' && player->x >= player->hero->left->x_pxl)
	{
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
	if (solong->movement.move[XK_d] && player->hero->right->index != '1' && player->x <= player->hero->right->x_pxl)
	{
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
	if (player->hero->index == 'C')
	{
		solong->info.coin--;
		player->hero->index = '0';
		player->hero->is_visited = 2;
	}
	if (solong->info.coin == 0)
		solong->info.exit = 1;
	if (player->hero->index == 'E' && solong->info.exit)
		exit((ft_clearall(solong), EXIT_SUCCESS));
	return (1);
}
