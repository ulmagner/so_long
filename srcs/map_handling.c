/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:27:57 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/24 01:57:55 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static int	get_info(t_info *info)
{
	int		nbr_line;
	int		nbr_column;

	nbr_line = 0;
	nbr_column = 0;
	if (!empty_string(info))
		return (0);
	if (!get_map(info, &nbr_line, &nbr_column))
		return (0);
	info->i_x = -1;
	info->i_y = 0;
	info->size_map = ft_strlen(info->map);
	info->nbr_line = nbr_line;
	if (info->map[info->size_map - 1] != '\n')
		info->size_map++;
	info->nbr_column = nbr_column;
	if (info->nbr_column <= 1 || info->nbr_line <= 1
		|| (info->nbr_column * info->nbr_line != info->size_map - nbr_line))
		return (ft_printf(2, "Error\nInvalid map\n"), 0);
	return (1);
}

static int	fill_map(t_info *info, t_map **head)
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
	while (++i < info->size_map - 1)
	{
		if (!make_list(info, &i, &node))
			return (free(row), 0);
		chain_map(&curr, head, node);
		chain_map_updown(node, info, head, &curr);
	}
	if (*head)
	{
		curr->right = NULL;
		(*head)->left = curr;
	}
	return (free(row), 1);
}

void	print_map(t_map **head, t_info *info)
{
	t_map	*row;
	t_map	*col;

	row = *head;
	while (row)
	{
		col = row;
		while (col)
		{
			printf("%c", col->index);
			if (col->x == info->nbr_column - 1)
				break ;
			col = col->right;
		}
		printf("\n");
		if (col->y == info->nbr_line - 1)
			break ;
		row = row->down;
	}
}

int	map_handling(t_info *info, t_map **map)
{
	if (!get_info(info))
		return (0);
	printf("%d %d %d\n", info->nbr_column, info->nbr_line, info->size_map);
	if (!fill_map(info, map))
		return (0);
	printf("%s\n\n", info->map);
	if (!check_close_map(map, info))
		return (0);
	print_map(map, info);
	return (1);
}
