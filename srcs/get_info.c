/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:29:34 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/25 19:04:31 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	empty_string(t_info *info)
{
	info->map = malloc(1);
	if (!info->map)
		return (0);
	info->map[0] = '\0';
	return (1);
}

int	get_map(t_info *info, int *nbr_line, int *nbr_column)
{
	char	*line;
	char	*tmp;
	int		i;

	line = ft_get_next_line(info->fd);
	*nbr_column = ft_strlen(line) - 1;
	while (line != NULL)
	{
		i = -1;
		while (line[++i])
			if (!ft_isstrchr("01CEP\n", line[i]))
				return (free(line), ft_printf(2, "Error\nCarte\n"), 0);
		tmp = ft_strjoin(info->map, line);
		if (!tmp)
			return (free(line), 0);
		free(info->map);
		info->map = tmp;
		free(line);
		(*nbr_line)++;
		line = ft_get_next_line(info->fd);
	}
	if (!check_ep_doubles(info))
		return (ft_printf(2, "Error\nCarte\n"), 0);
	return (1);
}
