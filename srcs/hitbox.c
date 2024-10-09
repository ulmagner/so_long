/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:59:51 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 18:00:04 by ulmagner         ###   ########.fr       */
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
