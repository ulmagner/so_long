/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:59:30 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/22 13:34:54 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	init_distances(t_all *all, t_info *info)
{
	all->dist.p_c = ft_calloc(info->collectible, sizeof(float));
	if (!all->dist.p_c)
		return (0);
	all->dist.p_o = ft_calloc(info->ennemies * info->oeil, sizeof(float));
	if (!all->dist.p_o)
		return (0);
	all->dist.p_t = ft_calloc(info->collectible, sizeof(float));
	if (!all->dist.p_t)
		return (0);
	return (1);
}

int	calcul_dist(t_all *all)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = -1;
	while (++j < all->info.oeil)
	{
		i = -1;
		while (++i < all->info.ennemies)
		{
			all->dist.p_o[++k] = calculate_distance(&all->player, \
				all->oeil[j][i].x, all->oeil[j][i].y, 0);
		}
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
