/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:38:11 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 19:46:39 by ulmagner         ###   ########.fr       */
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
	if (ft_strnstr(line, "lanceflamme", ft_strlen(line)))
	{
		if (ft_strnstr(line, "bas", ft_strlen(line)))
			info->nbr_a[23]++;
		if (line[0] == '-' || line[0] == '.')
			info->nbr_i[7]++;
	}
}
