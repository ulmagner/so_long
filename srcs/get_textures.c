/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:35:58 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/11 12:06:06 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	check_floor(char *line, t_info *info)
{
	if (ft_strnstr(line, "floor", ft_strlen(line)))
	{
		info->nbr_a[0]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[0]++;
	}
}

void	check_wall(char *line, t_info *info)
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

void	check_deco(char *line, t_info *info)
{
	if (ft_strnstr(line, "deco", ft_strlen(line)))
	{
		if (ft_strnstr(line, "tree", ft_strlen(line)))
			info->nbr_a[6]++;
		else if (ft_strnstr(line, "loot", ft_strlen(line)))
			info->nbr_a[7]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[2]++;
	}
}

void	check_exit(char *line, t_info *info)
{
	if (ft_strnstr(line, "exit", ft_strlen(line)))
	{
		info->nbr_a[8]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[3]++;
	}
}

void	check_slime(char *line, t_info *info)
{
	if (ft_strnstr(line, "slime", ft_strlen(line)))
	{
		if (ft_strnstr(line, "jar", ft_strlen(line)))
			info->nbr_a[9]++;
		else if (ft_strnstr(line, "run", ft_strlen(line)))
			info->nbr_a[10]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[4]++;
	}
}
