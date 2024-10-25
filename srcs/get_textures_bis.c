/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:38:11 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/22 14:15:12 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	check_player(char *line, t_info *info)
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
		else if (ft_strnstr(line, "dead", ft_strlen(line)))
			info->nbr_a[19]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[5]++;
	}
}

void	check_ennemies(char *line, t_info *info)
{
	if (ft_strnstr(line, "ennemies", ft_strlen(line)))
	{
		if (ft_strnstr(line, "gauche", ft_strlen(line)))
			info->nbr_a[20]++;
		else if (ft_strnstr(line, "droite", ft_strlen(line)))
			info->nbr_a[21]++;
		else if (ft_strnstr(line, "dead", ft_strlen(line)))
			info->nbr_a[22]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[6]++;
	}
}

void	check_trap(char *line, t_info *info)
{
	if (ft_strnstr(line, "trap", ft_strlen(line)))
	{
		if (ft_strnstr(line, "bas", ft_strlen(line)))
			info->nbr_a[23]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[7]++;
	}
}

void	check_plan(char *line, t_info *info)
{
	if (ft_strnstr(line, "game", ft_strlen(line)))
	{
		if (ft_strnstr(line, "died", ft_strlen(line)))
			info->nbr_a[24]++;
		else if (ft_strnstr(line, "minimap", ft_strlen(line)))
			info->nbr_a[25]++;
		else if (ft_strnstr(line, "red", ft_strlen(line)))
			info->nbr_a[26]++;
		else if (ft_strnstr(line, "bleu", ft_strlen(line)))
			info->nbr_a[27]++;
		else if (ft_strnstr(line, "green", ft_strlen(line)))
			info->nbr_a[28]++;
		else if (ft_strnstr(line, "hero", ft_strlen(line)))
			info->nbr_a[29]++;
		else if (ft_strnstr(line, "countdown", ft_strlen(line)))
			info->nbr_a[30]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[8]++;
	}
}
