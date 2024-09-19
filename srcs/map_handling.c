/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:27:57 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/19 16:02:09 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	get_map(t_info *info)
{
	char	*line;
	char	*tmp;
	int		i;
	int		nbr_line;

	nbr_line = 0;
	info->map = malloc(1);
	if (!info->map)
		return (0);
	info->map[0] = '\0';
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
		nbr_line++;
		line = ft_get_next_line(info->fd);
	}
	info->size_line = ft_strlen(info->map) / nbr_line;
	return (1);
}

static t_map	*ft_newnode(t_info *info, int x, int y)
{
	t_map	*node;

	node = malloc(sizeof(t_map));
	if (!node)
		return (NULL);
	node->index = info->map[x];
	node->x = x;
	node->y = y;
	node->right = node;
	node->left = node;
	node->up = node;
	node->down = node;
	return (node);
}

static void	chain_map(t_map **curr, t_map **head, t_map *node)
{
	if (!(*head))
	{
		*head = node;
		*curr = *head;
	}
	else
	{
		(*curr)->right = node;
		node->left = *curr;
		*curr = node;
	}
}

int	fill_map(t_info *info, int x, t_map **head)
{
	t_map	*curr;
	t_map	*node;
	int		y;

	y = 0;
	*head = NULL;
	curr = NULL;
	while (++x < info->size_line)
	{
		if (info->map[x] == '\n')
		{
			x = -1;
			y++;
			continue ;
		}
		node = ft_newnode(info, x, y);
		if (!node)
			return (0);
		chain_map(&curr, head, node);
	}
	if (*head)
	{
		curr->right = *head;
		(*head)->left = curr;
	}
	return (1);
}

int	map_handling(t_info *info, t_map **map, int format)
{
	if (!get_map(info))
		return (0);
	if (!fill_map(info, format, map))
		return (0);
	printf("%s", info->map);
	return (1);
}
