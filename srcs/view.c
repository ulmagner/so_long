/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:19:26 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/15 14:19:41 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	init_view(t_all *all, t_view *view)
{
	view->w = (all->info.column * 64) / 4;
	view->h = (all->info.line * 64) / 4;
	view->x = all->player.x - (view->w / 2);
	view->y = all->player.y - (view->h / 2);
	return (1);
}

int	set_view_to_ppos(t_view *view, t_player *player, t_all *all)
{
	view->x = player->x - (view->w / 2);
	view->y = player->y - (view->h / 2);
	if (view->x < 0)
		view->x = 0;
	else if (view->x + view->w > all->plan.w)
		view->x = all->plan.w - view->w;
	if (view->y < 0)
		view->y = 0;
	else if (view->y + view->h > all->plan.h)
		view->y = all->plan.h - view->h;
	return (1);
}
