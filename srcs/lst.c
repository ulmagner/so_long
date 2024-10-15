/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:38:08 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/15 16:16:15 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

t_map	**init_row_lst(t_info *info)
{
	t_map	**row;
	int		i;

	i = -1;
	row = malloc(sizeof(t_map *) * info->column);
	if (!row)
		return (NULL);
	while (++i < info->column)
		row[i] = NULL;
	return (row);
}

static t_map	*ft_newnode(t_info *info, int *i, t_map **h, t_all *all)
{
	t_map	*node;
	int		j;

	j = -1;
	node = malloc(sizeof(t_map));
	if (!node)
		return (NULL);
	node->i = info->map[*i];
	node->is_visited = 0;
	node->x = info->i_x;
	node->y = info->i_y;
	node->x_pxl = node->x * TILE_SIZE;
	node->y_pxl = node->y * TILE_SIZE;
	node->right = NULL;
	node->left = NULL;
	node->up = NULL;
	node->down = NULL;
	if (node->i == 'P')
		*h = node;
	while (++j < info->ennemies)
	{
		if (node->i == 'O')
			(all->oeil[j]).o = node;
	}
	if (node->i == 'C')
		(all->slime[info->slime++]).c = node;
	if (node->i == 'F')
		(all->trap[info->fire++]).t = node;
	return (node);
}

void	chain_map(t_map **curr, t_map **head, t_map *node)
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

void	chain_map_updown(t_map *node, t_info *info, t_map **head, t_map **curr)
{
	t_map	*temp;

	if (info->i_y == 0)
		node->up = NULL;
	else
	{
		temp = *head;
		while (temp && (temp->x != node->x || temp->y != node->y - 1))
			temp = temp->right;
		if (temp)
		{
			node->up = temp;
			temp->down = node;
		}
	}
	*curr = node;
}

int	make_list(t_info *info, int *i, t_map **node, t_map **h, t_all *all)
{
	++info->i_x;
	if (info->i_x == info->column)
	{
		info->i_x = 0;
		info->i_y++;
		(*i)++;
	}
	*node = ft_newnode(info, i, h, all);
	if (!*node)
		return (0);
	return (1);
}
