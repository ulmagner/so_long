/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tileset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:40:34 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/25 20:18:48 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

// static void	create_image(t_image *image, t_window *window)
// {
// 	image->img = mlx_xpm_file_to_image(window->mlx, \
// 		image->img_path, &image->width, &image->height);
// 	image->addr = mlx_get_data_addr(image->img, \
// 		&image->bits_per_pixel, &image->line_length, &image->endian);
// }

t_image	**split_tileset(t_solong *solong)
{
	t_image	**tileset;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = -1;
	tileset = malloc(sizeof(t_image *) * (solong->info.nbr_image));
	ft_printf(2, "%d\n", solong->info.nbr_image);
	while (++i < 6)
	{
		j = -1;
		tileset[i] = malloc(sizeof(t_image) * (solong->info.nbr_i[i]));
		ft_printf(2, "%d\n", solong->info.nbr_i[i]);
		while (++j < solong->info.nbr_i[i])
		{
			solong->tileset[i][j].img_path = solong->info.path_texture[k];
			ft_printf(2, "%s\n", solong->info.path_texture[k]);
			// create_image(&solong->tileset[i][j], &solong->window);
			k++;
		}
	}
	return (tileset);
}

char *empty_stringe(char *path)
{
	path = malloc(1);
	if (!path)
		return (NULL);
	path[0] = '\0';
	return (path);
}

int	get_paths(char *file, t_info *info)
{
	char	*line;
	int		fd;
	char	*tmp;
	char	*path;

	path = NULL;
	path = empty_stringe(path);
	if (!path)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	line = ft_get_next_line(fd);
	info->nbr_i = malloc(sizeof(int) * 7);
	if (!info->nbr_i)
		return (0);
	ft_bzero(info->nbr_i, 7);
	while (line)
	{
		if (ft_strnstr(line, "floor", ft_strlen(line)))
			info->nbr_i[0]++;
		if (ft_strnstr(line, "wall", ft_strlen(line)))
			info->nbr_i[1]++;
		if (ft_strnstr(line, "deco", ft_strlen(line)))
			info->nbr_i[2]++;
		if (ft_strnstr(line, "exit", ft_strlen(line)))
			info->nbr_i[3]++;
		if (ft_strnstr(line, "coin", ft_strlen(line)))
			info->nbr_i[4]++;
		if (ft_strnstr(line, "player", ft_strlen(line)))
			info->nbr_i[5]++;
		tmp = ft_strjoin(path, line);
		if (!tmp)
			return (free(path), free(line), close(fd), 0);
		free(path);
		path = tmp;
		free(line);
		info->nbr_image++;
		line = ft_get_next_line(fd);
	}
	info->path_texture = ft_split(path, '\n');
	if (!info->path_texture)
		return (close(fd), free(path), 0);
	int i = -1;
	while (info->path_texture[++i])
		ft_printf(2, "%s\n", info->path_texture[i]);
	int j;
	j = -1;
	while (info->nbr_i[++j])
		ft_printf(2, "%d\n", info->nbr_i[j]);
	return (free(path), close(fd), 1);
}
