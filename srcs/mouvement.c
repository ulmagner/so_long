/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:40:44 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/26 14:39:57 by ulmagner         ###   ########.fr       */
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
	if (solong->i % 32 != 0)
		return (0);
	if (solong->movement.move[XK_w] && solong->player.hero->up->index != '1')
	{
		solong->player.hero = solong->player.hero->up;
	}
	if (solong->movement.move[XK_s] && solong->player.hero->down->index != '1')
	{
		solong->player.hero = solong->player.hero->down;
	}
	if (solong->movement.move[XK_a] && solong->player.hero->left->index != '1')
	{
		solong->player.hero = solong->player.hero->left;
	}
	if (solong->movement.move[XK_d] && solong->player.hero->right->index != '1')
	{
		solong->player.hero = solong->player.hero->right;
	}
	return (1);
}
