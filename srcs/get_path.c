/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:53:47 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/16 12:53:33 by ulmagner         ###   ########.fr       */
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

	check_floor(*line, info);
	check_wall(*line, info);
	check_deco(*line, info);
	check_exit(*line, info);
	check_slime(*line, info);
	check_player(*line, info);
	check_ennemies(*line, info);
	check_trap(*line, info);
	check_plan(*line, info);
	if (*line[0] == '.')
		info->nbr_image++;
	tmp = ft_strjoin(*path, *line + 1);
	if (!tmp)
		return (free(*line), 0);
	free(*path);
	*path = tmp;
	free(*line);
	return (1);
}

static int	init_i(t_info *info)
{
	info->nbr_i = ft_calloc(9, sizeof(int));
	if (!info->nbr_i)
		return (0);
	info->nbr_a = ft_calloc(30, sizeof(int));
	if (!info->nbr_a)
		return (free(info->nbr_i), 0);
	return (info->nbr_i && info->nbr_a);
}

int	get_paths(char *file, t_info *info)
{
	char	*line;
	int		fd;
	char	*path;

	path = empty_stringe(NULL);
	if (!path || !init_i(info))
		return (free(path), 0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (free(path), 0);
	line = ft_get_next_line(fd);
	if (!line)
		return (close(fd), free(path), 0);
	while (line)
	{
		if (!parse_file(&line, info, &path))
			return (free(line), close(fd), free(path), 0);
		line = ft_get_next_line(fd);
	}
	info->path_texture = ft_split(path, '\n');
	if (!info->path_texture)
		return (close(fd), free(path), free(line), exit(0), 0);
	return (free(path), close(fd), 1);
}
