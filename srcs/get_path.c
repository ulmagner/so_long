/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:53:47 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/07 14:00:52 by ulysse           ###   ########.fr       */
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

static void	check_floor(char *line, t_info *info)
{
	if (ft_strnstr(line, "floor", ft_strlen(line)))
	{
		info->nbr_a[0]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[0]++;
	}
}

static void	check_wall(char *line, t_info *info)
{
	if (ft_strnstr(line, "wall", ft_strlen(line)))
	{
		if (ft_strnstr(line, "haut", ft_strlen(line)))
			info->nbr_a[1]++;
		else if (ft_strnstr(line, "bas", ft_strlen(line)))
			info->nbr_a[2]++;
		else if (ft_strnstr(line, "gauche", ft_strlen(line)))
			info->nbr_a[3]++;
		else if (ft_strnstr(line, "droite", ft_strlen(line)))
			info->nbr_a[4]++;
		else if (ft_strnstr(line, "corner", ft_strlen(line)))
			info->nbr_a[5]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[1]++;
	}
}

static void	check_deco(char *line, t_info *info)
{
	if (ft_strnstr(line, "deco", ft_strlen(line)))
	{
		if (ft_strnstr(line, "jar", ft_strlen(line)))
			info->nbr_a[6]++;
		else if (ft_strnstr(line, "tree", ft_strlen(line)))
			info->nbr_a[7]++;
		else if (ft_strnstr(line, "loot", ft_strlen(line)))
			info->nbr_a[8]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[2]++;
	}
}

static void	check_exit(char *line, t_info *info)
{
	if (ft_strnstr(line, "exit", ft_strlen(line)))
	{
		info->nbr_a[9]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[3]++;
	}
}

static void	check_slime(char *line, t_info *info)
{
	if (ft_strnstr(line, "slime", ft_strlen(line)))
	{
		if (ft_strnstr(line, "run", ft_strlen(line)))
			info->nbr_a[10]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[4]++;
	}
}

static void	check_player(char *line, t_info *info)
{
	if (ft_strnstr(line, "player", ft_strlen(line)))
	{
		if (ft_strnstr(line, "haut", ft_strlen(line)))
			info->nbr_a[11]++;
		else if (ft_strnstr(line, "bas", ft_strlen(line)))
			info->nbr_a[12]++;
		else if (ft_strnstr(line, "gauche", ft_strlen(line)))
			info->nbr_a[13]++;
		else if (ft_strnstr(line, "droite", ft_strlen(line)))
			info->nbr_a[14]++;
		else if (ft_strnstr(line, "attack_", ft_strlen(line)))
			info->nbr_a[15]++;
		else if (ft_strnstr(line, "attackr", ft_strlen(line)))
			info->nbr_a[16]++;
		else if (ft_strnstr(line, "counter_", ft_strlen(line)))
			info->nbr_a[17]++;
		else if (ft_strnstr(line, "counterr", ft_strlen(line)))
			info->nbr_a[18]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[5]++;
	}
}

static void	check_ennemies(char *line, t_info *info)
{
	if (ft_strnstr(line, "ennemies", ft_strlen(line)))
	{
		if (ft_strnstr(line, "gauche", ft_strlen(line)))
			info->nbr_a[19]++;
		else if (ft_strnstr(line, "droite", ft_strlen(line)))
			info->nbr_a[20]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[6]++;
	}
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
	info->nbr_i = ft_calloc(7, sizeof(int));
	info->nbr_a = ft_calloc(21, sizeof(int));
	return (info->nbr_i && info->nbr_a);
}

int	get_paths(char *file, t_info *info)
{
	char	*line;
	int		fd;
	char	*path;

	path = empty_stringe(NULL);
	if (!path || !init_index(info))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	line = ft_get_next_line(fd);
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
