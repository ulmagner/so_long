/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:44:27 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/26 17:55:18 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static void	ft_freewindow(t_window *window)
{
	mlx_destroy_window(window->mlx, window->main);
	mlx_destroy_display(window->mlx);
	free(window->mlx);
}

static void	ft_freeimage(t_solong *solong)
{
	int	i;
	int	j;

	i = -1;
	if (!solong->tileset || !*solong->tileset)
		return ;
	while (++i < solong->info.nbr_image)
	{
		j = -1;
		while (++j < solong->info.nbr_i[i])
		{
			mlx_destroy_image(solong->window.mlx, solong->tileset[i][j].img);
		}
		free(solong->tileset[i]);
	}
	free(solong->tileset);
	mlx_destroy_image(solong->window.mlx, solong->ground.img);
}

void	ft_clearall(t_solong *solong)
{
	ft_freemap(&solong->map);
	ft_freeimage(solong);
	ft_freeinfo(&solong->info);
	ft_freewindow(&solong->window);
	close(solong->info.fd);
}
