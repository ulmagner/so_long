/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:53:47 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/29 15:04:16 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static char	*empty_stringe(char *path)
{
	path = malloc(1);
	if (!path)
		return (NULL);
	path[0] = '\0';
	return (path);
}

static int	parse_file(char **line, t_info *info, char **path)
{
	char	*tmp;

	if (ft_strnstr(*line, "floor", ft_strlen(*line)))
	{
		info->nbr_a[0]++;
		if (*line[0] == '-' || *line[0] == '.')
			info->nbr_i[0]++;
	}
	if (ft_strnstr(*line, "wall", ft_strlen(*line)))
	{
		if (ft_strnstr(*line, "haut", ft_strlen(*line)))
			info->nbr_a[1]++;
		else if (ft_strnstr(*line, "bas", ft_strlen(*line)))
			info->nbr_a[2]++;
		else if (ft_strnstr(*line, "gauche", ft_strlen(*line)))
			info->nbr_a[3]++;
		else if (ft_strnstr(*line, "droite", ft_strlen(*line)))
			info->nbr_a[4]++;
		if (*line[0] == '-' || *line[0] == '.')
			info->nbr_i[1]++;
	}
	if (ft_strnstr(*line, "deco", ft_strlen(*line)))
	{
		info->nbr_a[5]++;
		if (*line[0] == '-' || *line[0] == '.')
			info->nbr_i[2]++;
	}
	if (ft_strnstr(*line, "exit", ft_strlen(*line)))
	{
		info->nbr_a[6]++;
		if (*line[0] == '-' || *line[0] == '.')
			info->nbr_i[3]++;
	}
	if (ft_strnstr(*line, "coin", ft_strlen(*line)))
	{
		info->nbr_a[7]++;
		if (*line[0] == '-' || *line[0] == '.')
			info->nbr_i[4]++;
	}
	if (ft_strnstr(*line, "player", ft_strlen(*line)))
	{
		if (ft_strnstr(*line, "nord", ft_strlen(*line)))
			info->nbr_a[8]++;
		else if (ft_strnstr(*line, "sud", ft_strlen(*line)))
			info->nbr_a[9]++;
		else if (ft_strnstr(*line, "gauche", ft_strlen(*line)))
			info->nbr_a[10]++;
		else if (ft_strnstr(*line, "est", ft_strlen(*line)))
			info->nbr_a[11]++;
		if (*line[0] == '-' || *line[0] == '.')
			info->nbr_i[5]++;
	}
	if (*line[0] == '.')
		info->nbr_image++;
	tmp = ft_strjoin(*path, *line + 1);
	if (!tmp)
		return (0);
	free(*path);
	*path = tmp;
	free(*line);
	return (1);
}

static int	init_index(t_info *info)
{
	info->nbr_i = malloc(sizeof(int) * 6);
	if (!info->nbr_i)
		return (0);
	info->nbr_a = malloc(sizeof(int) * 12);
	if (!info->nbr_a)
		return (0);
	ft_bzero(info->nbr_i, sizeof(int) * 6);
	ft_bzero(info->nbr_a, sizeof(int) * 12);
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
	if (!init_index(info))
		return (0);
	while (line)
	{
		if (!parse_file(&line, info, &path))
			return (free(line), close(fd), free(path), 0);
		line = ft_get_next_line(fd);
	}
	info->path_texture = ft_split(path, '\n');
	if (!info->path_texture)
		return (close(fd), free(path), 0);
	return (free(path), close(fd), 1);
}
