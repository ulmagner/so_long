/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:59:30 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/16 16:12:20 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	init_distances(t_all *all)
{
	all->dist.p_c = ft_calloc(all->info.collectible, sizeof(float));
	if (!all->dist.p_c)
		return (0);
	all->dist.p_o = ft_calloc(all->info.ennemies, sizeof(float));
	if (!all->dist.p_o)
		return (0);
	all->dist.p_t = ft_calloc(all->info.collectible, sizeof(float));
	if (!all->dist.p_t)
		return (0);
	return (1);
}

int	calcul_dist(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->info.ennemies)
	{
		all->dist.p_o[i] = calculate_distance(&all->player, \
			all->oeil[i].x, all->oeil[i].y, 0);
	}
	i = -1;
	while (++i < all->info.collectible)
		all->dist.p_c[i] = calculate_distance(&all->player, \
			all->slime[i].x, all->slime[i].y, 0);
	i = -1;
	while (++i < all->info.trap)
		all->dist.p_t[i] = calculate_distance(&all->player, \
			all->trap[i].x, all->trap[i].y, 0);
	return (1);
}
