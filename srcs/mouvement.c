/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:40:44 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/11 14:40:18 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	movement_p(int keycode, t_all *all)
{
	all->movement.move[keycode] = true;
	if (keycode == XK_Escape)
		exit((ft_clearall(all), EXIT_SUCCESS));
	return (0);
}

void	check_mouvment(t_player *player)
{
	if (player->animation[player->i] != 0)
		player->animation[player->i] = 0;
}

int	movement_r(int keycode, t_all *all)
{
	all->movement.move[keycode] = false;
	check_mouvment(&all->player);
	return (0);
}

int	movement_handling(t_all *all)
{
	if (!all->attack.button)
	{
		dir_up(&all->player, &all->movement, all);
		dir_down(&all->player, &all->movement, all);
		dir_left(&all->player, &all->movement, all);
		dir_right(&all->player, &all->movement, all);
	}
	if (all->player.h->i == 'E' && all->info.exit \
		&& all->movement.move[XK_e])
		exit((ft_clearall(all), EXIT_SUCCESS));
	return (1);
}
