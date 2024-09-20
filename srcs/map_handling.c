/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:27:57 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/20 17:22:06 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	get_map(t_info *info, int *nbr_line)
{
	char	*line;
	char	*tmp;
	int		i;

	line = ft_get_next_line(info->fd);
	while (line != NULL)
	{
		i = -1;
		while (line[++i])
		{
			if (!ft_isstrchr("01CEP\n", line[i]))
				return (free(line), ft_printf(2, "Error\nCarte\n"), 0);
		}
		tmp = ft_strjoin(info->map, line);
		if (!tmp)
			return (free(line), 0);
		free(info->map);
		info->map = tmp;
		free(line);
		(*nbr_line)++;
		line = ft_get_next_line(info->fd);
	}
	return (1);
}

static int	get_info(t_info *info)
{
	int		nbr_line;

	nbr_line = 0;
	if (!empty_string(info))
		return (0);
	if (!get_map(info, &nbr_line))
		return (0);
	info->i_x = -1;
	info->i_y = 0;
	info->size_map = ft_strlen(info->map);
	info->nbr_line = nbr_line;
	info->nbr_column = info->size_map / nbr_line;
	return (1);
}

static void	print_map(t_map **map)
{
	t_map	*curr;

	curr = *map;
	while (curr != NULL)
	{
		printf("%c", curr->index);
		curr = curr->right;
	}
	printf("\n");
}

int	map_handling(t_info *info, t_map **map)
{
	if (!get_info(info))
		return (0);
	printf("%d %d %d\n", info->nbr_column, info->nbr_line, info->size_map);
	if (!fill_map(info, map))
		return (0);
	printf("%s\n\n", info->map);
	print_map(map);
	return (1);
}
