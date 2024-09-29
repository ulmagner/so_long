/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tileset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:40:34 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/29 15:03:42 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	create_image(t_image *image, t_window *window)
{
	image->img = mlx_xpm_file_to_image(window->mlx,
			image->img_path, &image->width, &image->height);
	if (!image->img)
		return (ft_printf(2, "Error\nTexture_path\n"), 0);
	image->addr = mlx_get_data_addr(image->img,
			&image->bits_per_pixel, &image->line_length, &image->endian);
	return (1);
}

static int	free_failedimage(int i, int j, int a, t_solong *solong)
{
	int	b;

	b = 0;
	while (a > 0)
		mlx_destroy_image(solong->window.mlx, solong->tileset[i][j][--a].img);
	free(solong->tileset[i][j]);
	while (i-- > 0)
	{
		j = solong->info.nbr_i[i];
		while (j > 0)
		{
			a = solong->info.nbr_a[b];
			while (a > 0)
				mlx_destroy_image(solong->window.mlx,
					solong->tileset[i][j][--a].img);
			free(solong->tileset[i][j--]);
		}
		free(solong->tileset[i]);
	}
	return (free(solong->tileset), 0);
}

int	split_tileset(t_solong *solong)
{
	int		i;
	int		j;
	int		k;
	int		a;
	int		b;

	k = 0;
	b = 0;
	i = -1;
	solong->tileset = malloc(sizeof(t_image **) * solong->info.nbr_image);
	while (++i < solong->info.nbr_image)
	{
		j = -1;
		solong->tileset[i] = malloc(sizeof(t_image *) * (solong->info.nbr_i[i]));
		while (++j < solong->info.nbr_i[i])
		{
			a = -1;
			solong->tileset[i][j] = malloc(sizeof(t_image) * (solong->info.nbr_a[b]));
			while (++a < solong->info.nbr_a[b] && solong->info.path_texture[k] != NULL)
			{
				ft_printf(2, "%d %d %d %d\n", i, j, a, b);
				solong->tileset[i][j][a].img_path = solong->info.path_texture[k];
				if (!create_image(&solong->tileset[i][j][a], &solong->window))
					return (free_failedimage(i, j, a, solong));
				k++;
			}
			b++;
		}
	}
	return (1);
}
