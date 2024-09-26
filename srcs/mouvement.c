/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:40:44 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/26 19:53:31 by ulmagner         ###   ########.fr       */
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

int	movement_handling(t_solong *solong)
{
	if (solong->i % 10 != 0)
		return (0);
	double speed;

	speed = 10;
	if (solong->movement.move[XK_w] && solong->player.hero->up->index != '1')
	{
		solong->player.hero->y_pxl -= speed;
		if (solong->player.hero->y_pxl <= solong->player.hero->up->y_pxl)
			solong->player.hero = solong->player.hero->up;
	}
	if (solong->movement.move[XK_s] && solong->player.hero->down->index != '1')
	{
		solong->player.hero->y_pxl += speed;
		if (solong->player.hero->y_pxl >= solong->player.hero->down->y_pxl)
			solong->player.hero = solong->player.hero->down;
	}
	if (solong->movement.move[XK_a] && solong->player.hero->left->index != '1')
	{
		solong->player.hero->x_pxl -= speed;
		if (solong->player.hero->x_pxl <= solong->player.hero->left->x_pxl)
			solong->player.hero = solong->player.hero->left;
	}
	if (solong->movement.move[XK_d] && solong->player.hero->right->index != '1')
	{
		solong->player.hero->x_pxl += speed;
		if (solong->player.hero->x_pxl >= solong->player.hero->right->x_pxl)
			solong->player.hero = solong->player.hero->right;
	}
	if (solong->player.hero->index == 'C')
	{
		solong->info.coin--;
		solong->player.hero->index = '0';
		solong->player.hero->is_visited = 2;
	}
	if (solong->info.coin == 0)
		solong->info.exit = 1;
	if (solong->player.hero->index == 'E' && solong->info.exit)
		exit((ft_clearall(solong), EXIT_SUCCESS));
	return (1);
}
