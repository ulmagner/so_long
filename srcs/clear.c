/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:44:27 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/18 18:23:33 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	ft_freewindow(t_window *window, t_all *all)
{
	if (all->ground.img)
		mlx_destroy_image(all->window.mlx, all->ground.img);
	if (all->plan.img)
		mlx_destroy_image(all->window.mlx, all->plan.img);
	if (all->game.img)
		mlx_destroy_image(all->window.mlx, all->game.img);
	if (window->mlx)
	{
		if (window->main)
			mlx_destroy_window(window->mlx, window->main);
		mlx_destroy_display(window->mlx);
		free(window->mlx);
	}
}

static void	ft_freeimage(t_all *all, int i)
{
	int	j;
	int	a;

	int (b) = 0;
	if (!all->tile || !*all->tile)
		return ;
	while (++i < all->info.nbr_image)
	{
		j = -1;
		while (++j < all->info.nbr_i[i])
		{
			a = -1;
			while (++a < all->info.nbr_a[b])
				mlx_destroy_image(all->window.mlx,
					all->tile[i][j][a].img);
			b++;
			free(all->tile[i][j]);
		}
		free(all->tile[i]);
	}
	free(all->tile);
}

void	ft_clearall(t_all *all)
{
	int	i;

	i = -1;
	ft_freemap(&all->map);
	ft_freeplayer(&all->player);
	if (all->trap)
		free(all->trap);
	if (all->slime)
		free(all->slime);
	if (all->oeil)
	{
		while (++i < all->info.oeil)
			if (all->oeil[i])
				free(all->oeil[i]);
		free(all->oeil);
	}
	i = -1;
	free(all->dist.p_c);
	free(all->dist.p_t);
	free(all->dist.p_o);
	ft_freeimage(all, i);
	ft_freeinfo(&all->info);
	ft_freewindow(&all->window, all);
	close(all->info.fd);
}
