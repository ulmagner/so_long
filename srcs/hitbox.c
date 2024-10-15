/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:59:51 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/15 16:41:07 by ulmagner         ###   ########.fr       */
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

int	get_hitbox_oeil(t_oeil *oeil)
{
	oeil->interaction[0][0] = oeil->x + 32;
	oeil->interaction[0][1] = oeil->y + 16;
	oeil->interaction[1][0] = oeil->x + 32;
	oeil->interaction[1][1] = oeil->y + 48;
	oeil->interaction[2][0] = oeil->x + 16;
	oeil->interaction[2][1] = oeil->y + 32;
	oeil->interaction[3][0] = oeil->x + 48;
	oeil->interaction[3][1] = oeil->y + 32;
	return (1);
}

int	check_hitbox_oeil(int interaction[4][2], t_oeil *oeil)
{
	int	x;
	int	y;
	int	i;

	i = -1;
	while (++i < 4)
	{
		x = interaction[i][0];
		y = interaction[i][1];
		if (x >= oeil->x && x <= oeil->x + 64 \
			&& y >= oeil->y && y <= oeil->y + 64)
			return (1);
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
