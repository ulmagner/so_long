/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:59:51 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 19:46:39 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	get_hitbox_player(t_player *player)
{
	player->interaction[0][0] = player->x + 32;
	player->interaction[0][1] = player->y;
	player->interaction[1][0] = player->x + 32;
	player->interaction[1][1] = player->y + 64;
	player->interaction[2][0] = player->x;
	player->interaction[2][1] = player->y + 32;
	player->interaction[3][0] = player->x + 64;
	player->interaction[3][1] = player->y + 32;
	return (1);
}

int	get_hitbox_oeuil(t_oeuil *oeuil)
{
	oeuil->interaction[0][0] = oeuil->x + 32;
	oeuil->interaction[0][1] = oeuil->y + 16;
	oeuil->interaction[1][0] = oeuil->x + 32;
	oeuil->interaction[1][1] = oeuil->y + 48;
	oeuil->interaction[2][0] = oeuil->x + 16;
	oeuil->interaction[2][1] = oeuil->y + 32;
	oeuil->interaction[3][0] = oeuil->x + 48;
	oeuil->interaction[3][1] = oeuil->y + 32;
	return (1);
}

int	check_hitbox_oeuil(int interaction[4][2], t_oeuil *oeuil)
{
	int	x;
	int	y;
	int	i;

	i = -1;
	while (++i < 4)
	{
		x = interaction[i][0];
		y = interaction[i][1];
		if (x >= oeuil->x && x <= oeuil->x + 64 \
			&& y >= oeuil->y && y <= oeuil->y + 64)
			return (1);
	}
	return (0);
}

int	check_hitbox_jar(int interaction[4][2], t_info info)
{
	int	x;
	int	y;
	int	i;
	int	j;

	j = -1;
	while (++j < info.collectible)
	{
		i = -1;
		while (++i < 4)
		{
			x = interaction[i][0];
			y = interaction[i][1];
			if (x >= info.deco[j][0] && x <= info.deco[j][0] + 64 \
				&& y >= info.deco[j][1] && y <= info.deco[j][1] + 64)
				return (1);
		}
	}
	return (0);
}

int	check_hitbox_player(int interaction[4][2], t_player *player)
{
	int	x;
	int	y;
	int	i;

	i = -1;
	while (++i < 4)
	{
		x = interaction[i][0];
		y = interaction[i][1];
		if (x >= player->x && x <= player->x + 64 \
			&& y >= player->y && y <= player->y + 64)
			return (1);
	}
	return (0);
}
