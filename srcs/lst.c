/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:38:08 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/20 17:21:51 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

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

static void	chain_map_updown(t_map *node, t_info *info, t_map **row)
{
	if (row[info->i_x])
	{
		node->up = row[info->i_x];
		row[info->i_x]->down = node;
	}
	row[info->i_x] = node;
}

static int	make_list(t_info *info, int i, t_map **node)
{
	++info->i_x;
	if (info->i_x == info->nbr_column)
	{
		info->i_x = 0;
		info->i_y++;
	}
	*node = ft_newnode(info, i);
	if (!*node)
		return (0);
	return (1);
}

int	fill_map(t_info *info, t_map **head)
{
	t_map	*curr;
	t_map	*node;
	t_map	**row;
	int		i;

	*head = NULL;
	curr = NULL;
	node = NULL;
	i = -1;
	row = init_row_lst(info);
	if (!row)
		return (0);
	while (++i < info->size_map)
	{
		if (!make_list(info, i, &node))
			return (free(row), 0);
		chain_map(&curr, head, node);
		chain_map_updown(node, info, row);
	}
	if (*head)
	{
		curr->right = NULL;
		(*head)->left = curr;
	}
	return (free(row), 1);
}
