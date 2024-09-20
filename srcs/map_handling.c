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
	info->i_x = -1;
	info->i_y = 0;
	info->size_map = ft_strlen(info->map);
	info->nbr_line = nbr_line;
	info->nbr_column = info->size_map / nbr_line;
	return (1);
}

static t_map	*ft_newnode(t_info *info, int i)
{
	t_map	*node;

	node = malloc(sizeof(t_map));
	if (!node)
		return (NULL);
	node->index = info->map[i];
	node->x = info->i_x;
	node->y = info->i_y;
	node->right = NULL;
	node->left = NULL;
	node->up = NULL;
	node->down = NULL;
	return (node);
}

static void	chain_map(t_map **curr, t_map **head, t_map *node, t_info *info, t_map *row[])
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
	if (row[info->i_x])
	{
		node->up = row[info->i_x];
		row[info->i_x]->down = node;
	}
	row[info->i_x] = node;
}

int	fill_map(t_info *info, t_map **head)
{
	t_map	*curr;
	t_map	*node;
	t_map	*row[info->nbr_column + 1];
	int		i;

	i = -1;
	*head = NULL;
	curr = NULL;
	while (++i < info->nbr_column)
		row[i] = NULL;
	i = -1;
	while (++i < info->size_map)
	{
		++info->i_x;
		if (info->i_x == info->nbr_column)
		{
			info->i_x = 0;
			info->i_y++;
		}
		node = ft_newnode(info, i);
		if (!node)
			return (0);
		chain_map(&curr, head, node, info, row);
	}
	if (*head)
	{
		curr->right = NULL;
		(*head)->left = curr;
	}
	return (1);
}

void	print_map(t_map **map)
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
	if (!get_map(info))
		return (0);
	printf("%d %d %d\n", info->nbr_column, info->nbr_line, info->size_map);
	if (!fill_map(info, map))
		return (0);
	printf("%s\n\n", info->map);
	print_map(map);
	return (1);
}
