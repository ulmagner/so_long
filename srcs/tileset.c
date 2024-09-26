/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tileset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:40:34 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/26 10:37:11 by ulmagner         ###   ########.fr       */
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

t_image	**split_tileset(t_solong *solong)
{
	t_image	**tileset;
	int		i;
	int		j;
	int		k;

	k = 0;
	i = -1;
	tileset = malloc(sizeof(t_image *) * solong->info.nbr_image);
	while (++i < solong->info.nbr_image)
	{
		j = -1;
		tileset[i] = malloc(sizeof(t_image) * (solong->info.nbr_i[i]));
		while (++j < solong->info.nbr_i[i])
		{
			tileset[i][j].img_path = solong->info.path_texture[k];
			if (!create_image(&tileset[i][j], &solong->window))
				return (free_failedimage(i, j, solong, tileset));
			k++;
		}
	}
	return (tileset);
}

char	*empty_stringe(char *path)
{
	path = malloc(1);
	if (!path)
		return (NULL);
	path[0] = '\0';
	return (path);
}

static int	parse_file(char **line, t_info *info, char **path, int fd)
{
	char	*tmp;

	if (ft_strnstr(*line, "floor", ft_strlen(*line)))
		info->nbr_i[0]++;
	if (ft_strnstr(*line, "wall", ft_strlen(*line)))
		info->nbr_i[1]++;
	if (ft_strnstr(*line, "deco", ft_strlen(*line)))
		info->nbr_i[2]++;
	if (ft_strnstr(*line, "exit", ft_strlen(*line)))
		info->nbr_i[3]++;
	if (ft_strnstr(*line, "coin", ft_strlen(*line)))
		info->nbr_i[4]++;
	if (ft_strnstr(*line, "player", ft_strlen(*line)))
		info->nbr_i[5]++;
	if (*line[0] == '.')
		info->nbr_image++;
	tmp = ft_strjoin(*path, *line + 1);
	if (!tmp)
		return (0);
	free(*path);
	*path = tmp;
	free(*line);
	*line = ft_get_next_line(fd);
	return (1);
}

int	get_paths(char *file, t_info *info)
{
	char	*line;
	int		fd;
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
		if (!parse_file(&line, info, &path, fd))
			return (free(line), close(fd), free(path), 0);
	info->path_texture = ft_split(path, '\n');
	if (!info->path_texture)
		return (close(fd), free(path), 0);
	return (free(path), close(fd), 1);
}
