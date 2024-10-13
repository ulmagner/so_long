/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tileset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:40:34 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/13 23:09:15 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	create_image(t_image *image, t_window *window)
{
	image->img = mlx_xpm_file_to_image(window->mlx,
			image->img_path, &image->w, &image->h);
	if (!image->img)
		return (ft_printf(2, "Error\nTexture_path\n"), 0);
	image->addr = mlx_get_data_addr(image->img,
			&image->bits_per_pixel, &image->line_length, &image->endian);
	return (1);
}

static int	free_failedimage(int i, int j, int a, t_all *all)
{
	int	b;

	b = 0;
	while (a > 0)
		mlx_destroy_image(all->window.mlx, all->tileset[i][j][--a].img);
	free(all->tileset[i][j]);
	while (i-- > 0)
	{
		j = all->info.nbr_i[i];
		while (j > 0)
		{
			a = all->info.nbr_a[b];
			while (a > 0)
				mlx_destroy_image(all->window.mlx,
					all->tileset[i][j][--a].img);
			free(all->tileset[i][j--]);
		}
		free(all->tileset[i]);
	}
	return (free(all->tileset), 0);
}

static void	init_i(int *i, int *k, int *b)
{
	*i = -1;
	*k = -1;
	*b = -1;
}

int	split_tileset(t_all *all, t_info *info)
{
	int		i;
	int		j;
	int		k;
	int		a;
	int		b;

	init_i(&i, &k, &b);
	all->tileset = malloc(sizeof(t_image **) * info->nbr_image);
	while (++i < info->nbr_image)
	{
		j = -1;
		all->tileset[i] = malloc(sizeof(t_image *) * info->nbr_i[i]);
		while (++j < info->nbr_i[i])
		{
			a = -1;
			all->tileset[i][j] = malloc(sizeof(t_image) * info->nbr_a[++b]);
			while (++a < info->nbr_a[b])
			{
				all->tileset[i][j][a].img_path = info->path_texture[++k];
				if (!create_image(&all->tileset[i][j][a], &all->window))
					return (free_failedimage(i, j, a, all));
			}
		}
	}
	return (1);
}
