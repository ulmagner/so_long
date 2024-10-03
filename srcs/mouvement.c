/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:40:44 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/03 10:24:11 by ulysse           ###   ########.fr       */
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

void	check_mouvment(t_player *player)
{
	if (player->animation[player->index] != 0)
		player->animation[player->index] = 0;
}

int	movement_r(int keycode, t_solong *solong)
{
	solong->movement.move[keycode] = false;
	// check_mouvment(&solong->player);
	return (0);
}

int	movement_handling(t_solong *solong)
{
	if (solong->i % 10 != 0)
		return (0);
	solong->player.ms = 8;
	dir_up(&solong->player, solong->movement, solong);
	dir_down(&solong->player, solong->movement, solong);
	dir_left(&solong->player, solong->movement, solong);
	dir_right(&solong->player, solong->movement, solong);
	if (solong->player.hero->index == 'C' && solong->movement.move[XK_e])
	{
		solong->info.coin--;
		solong->player.hero->index = '0';
		solong->player.hero->is_visited = 2;
	}
	if (solong->info.coin == 0)
		solong->info.exit = 1;
	if (solong->player.hero->index == 'E' && solong->info.exit \
		&& solong->movement.move[XK_e])
		exit((ft_clearall(solong), EXIT_SUCCESS));
	return (1);
}
