/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:40:34 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/15 19:21:25 by ulmagner         ###   ########.fr       */
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

static int	free_failedimage(t_fail *fail, t_all *all, t_image ****t)
{
	while (--(fail->a) > 0)
		mlx_destroy_image(all->window.mlx, (*t)[fail->i][fail->j][fail->a].img);
	free((*t)[fail->i][fail->j]);
	while (--(fail->j) >= 0)
	{
		fail->a = all->info.nbr_a[--(fail->b)];
		while (--(fail->a) >= 0)
			mlx_destroy_image(all->window.mlx,
				(*t)[fail->i][fail->j][fail->a].img);
		free((*t)[fail->i][fail->j]);
	}
	while (--(fail->i) >= 0)
	{
		fail->j = all->info.nbr_i[fail->i];
		while (--(fail->j) >= 0)
		{
			fail->a = all->info.nbr_a[--(fail->b)];
			while (--(fail->a) >= 0)
				mlx_destroy_image(all->window.mlx,
					(*t)[fail->i][fail->j][fail->a].img);
			free((*t)[fail->i][fail->j]);
		}
		free((*t)[fail->i]);
	}
	return (free((*t)), (*t) = NULL, 0);
}

static void	init_fail(t_fail *fail)
{
	fail->i = -1;
	fail->k = -1;
	fail->b = -1;
}

int	split_tile(t_all *all, t_info *info, t_fail *fail)
{
	init_fail(&all->fail);
	all->tile = malloc(sizeof(t_image **) * info->nbr_image);
	while (++(fail->i) < info->nbr_image)
	{
		fail->j = -1;
		all->tile[fail->i] = malloc(sizeof(t_image *) * info->nbr_i[fail->i]);
		while (++(fail->j) < info->nbr_i[fail->i])
		{
			fail->a = -1;
			all->tile[fail->i][fail->j] = malloc(sizeof(t_image) \
				* info->nbr_a[++(fail->b)]);
			while (++(fail->a) < info->nbr_a[fail->b])
			{
				all->tile[fail->i][fail->j][fail->a].img_path \
					= info->path_texture[++(fail->k)];
				if (!create_image(&all->tile[fail->i][fail->j][fail->a], \
					&all->window))
					return (free_failedimage(&all->fail, all, &all->tile));
			}
		}
	}
	return (1);
}
