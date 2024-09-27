/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tileset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:40:34 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/27 16:07:40 by ulmagner         ###   ########.fr       */
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

t_image	**free_failedimage(int i, int j, t_solong *solong, t_image **tileset)
{
	while (j > 0)
		mlx_destroy_image(solong->window.mlx, tileset[i][--j].img);
	free(tileset[i]);
	while (i-- > 0)
	{
		j = solong->info.nbr_i[i];
		while (j > 0)
			mlx_destroy_image(solong->window.mlx, tileset[i][--j].img);
		free(tileset[i]);
	}
	return (free(tileset), NULL);
}

t_image	***split_tileset(t_solong *solong)
{
	t_image	***tileset;
	int		i;
	int		j;
	int		k;
	int		a;

	k = 0;
	i = -1;
	tileset = malloc(sizeof(t_image **) * solong->info.nbr_image);
	while (++i < solong->info.nbr_image)
	{
		j = -1;
		tileset[i] = malloc(sizeof(t_image *) * (solong->info.nbr_i[i]));
		ft_printf(2, "\nnbr_image:%d ", i);
		while (++j < solong->info.nbr_i[i])
		{
			a = -1;
			// ft_printf(2, "nbr_i:%d ", solong->info.nbr_i[i]);
			tileset[i][j] = malloc(sizeof(t_image) * (solong->info.nbr_a[j]));
			while (++a < solong->info.nbr_a[j])
			{
				ft_printf(2, "nbr_a:%d path%s ", solong->info.nbr_a[j], solong->info.path_texture[k]);
				tileset[i][j][a].img_path = solong->info.path_texture[k];
				if (!create_image(&tileset[i][j][a], &solong->window))
					return (/*free_failedimage(i, j, solong, tileset)*/NULL);
				k++;
			}
		}
	}
	return (tileset);
}
