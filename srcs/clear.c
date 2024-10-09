/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:44:27 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 19:46:39 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	ft_freewindow(t_window *window)
{
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
	int	b;

	b = 0;
	if (!all->tileset || !*all->tileset)
		return ;
	while (++i < all->info.nbr_image)
	{
		j = -1;
		while (++j < all->info.nbr_i[i])
		{
			a = -1;
			while (++a < all->info.nbr_a[b])
				mlx_destroy_image(all->window.mlx,
					all->tileset[i][j][a].img);
			b++;
			free(all->tileset[i][j]);
		}
		free(all->tileset[i]);
	}
	free(all->tileset);
	mlx_destroy_image(all->window.mlx, all->ground.img);
	mlx_destroy_image(all->window.mlx, all->game.img);
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
	if (all->oeuil)
		free(all->oeuil);
	ft_freeimage(all, i);
	ft_freeinfo(&all->info);
	ft_freewindow(&all->window);
	close(all->info.fd);
}
