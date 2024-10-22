/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleportation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:36:03 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/22 18:50:11 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

float	calculate_distance_s(t_slime *slime, float obj_x, float obj_y, int off)
{
	return (sqrt(pow(slime->x + off - obj_x, 2) \
		+ pow(slime->y + off - obj_y, 2)));
}

void	teleportation(t_slime *slime, t_all *all)
{
	int (att_x_window) = all->attack.x - all->window.main_w / 2
		+ (all->view.x + all->view.w / 2);
	int (att_y_window) = all->attack.y - all->window.main_h / 2
		+ (all->view.y + all->view.h / 2);
	if (all->movement.move[XK_Shift_L] && all->attack.button)
	{
		if (slime->x <= att_x_window)
			slime->x += 4;
		else if (slime->x >= att_x_window)
			slime->x -= 4;
		if (slime->y <= att_y_window)
			slime->y += 4;
		else if (slime->y >= att_y_window)
			slime->y -= 4;
		slime->waiting = 1;
	}
	if (slime->waiting && all->counter.button)
	{
		if (calculate_distance_s(slime, att_x_window, att_y_window, 0) <= 32.0f)
		{
			all->player.x = slime->x;
			all->player.y = slime->y;
			slime->waiting = 0;
		}
	}
}
