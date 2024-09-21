/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:38:08 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/21 20:30:20 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

t_map	**init_row_lst(t_info *info)
{
	t_map	**row;
	int		i;

	i = -1;
	row = malloc(sizeof(t_map *) * info->nbr_column);
	if (!row)
		return (NULL);
	while (++i < info->nbr_column)
		row[i] = NULL;
	return (row);
}

static t_map	*ft_newnode(t_info *info, int *i)
{
	t_map	*node;

	node = malloc(sizeof(t_map));
	if (!node)
		return (NULL);
	node->index = info->map[*i];
	node->x = info->i_x;
	node->y = info->i_y;
	node->right = NULL;
	node->left = NULL;
	node->up = NULL;
	node->down = NULL;
	return (node);
}

void	chain_map(t_map **curr, t_map **head, t_map *node, t_info *info)
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
    t_map *temp;

    // If we're on the first row (info->i_y == 0), no "up" link is needed
    if (info->i_y == 0)
    {
        node->up = NULL; // No node above
    }
    else
    {
        // Traverse upwards from the current node in the previous row
        temp = *head;

        while (temp && (temp->x != node->x || temp->y != node->y - 1))
        {
            temp = temp->right; // Move right to find the node directly above
        }

        // If we found the node in the previous row, link them
        if (temp)
        {
            node->up = temp;
            temp->down = node;
        }
    }

    // Set the current node to the newly created node
    *curr = node;

}

void	chain_map_updown(t_map *node, t_info *info, t_map **row)
{
	if (row[info->i_x])
	{
		node->up = row[info->i_x];
		row[info->i_x]->down = node;
	}
	row[info->i_x] = node;
}

int	make_list(t_info *info, int *i, t_map **node)
{
	++info->i_x;
	if (info->i_x == info->nbr_column)
	{
		info->i_x = 0;
		info->i_y++;
		(*i)++;
	}
	*node = ft_newnode(info, i);
	if (!*node)
		return (0);
	return (1);
}
