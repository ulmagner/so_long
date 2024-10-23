/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:27:57 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/22 13:20:23 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static t_map	**init_row_lst(t_info *info)
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

static int	get_info(t_info *info)
{
	int		line;
	int		column;

	line = 0;
	column = 0;
	if (!empty_string(info))
		return (0);
	if (!get_map(info, &line, &column))
		return (0);
	info->i_x = 0;
	info->i_y = 0;
	info->size_map = ft_strlen(info->map);
	info->line = line;
	info->column = column;
	if (info->map[info->size_map - 1] != '\n')
		info->size_map++;
	if (info->column <= 1 || info->line <= 1
		|| (info->column * info->line != info->size_map - line))
		return (ft_printf(2, "Error\nInvalid map\n"), 0);
	return (1);
}

static int	fill_map(t_info *info, t_map **head, t_map **h, t_all *all)
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
		if (!make_list(&i, &node, h, all))
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
			ft_printf(1, "%c", col->i);
			if (col->x == info->column - 1)
				break ;
			col = col->right;
		}
		ft_printf(1, "\n");
		if (col->y == info->line - 1)
			break ;
		row = row->down;
	}
}

int	map_handling(t_info *info, t_map **map, t_player *player, t_all *all)
{
	int	i;
	int	j;

	if (!get_info(info))
		return (0);
	if (!init_char(all, info))
		return (0);
	j = -1;
	while (++j < info->oeil)
	{
		i = -1;
		while (++i < info->ennemies)
			all->oeil[j][i].anim = get_randoms(0, 5, 7);
	}
	if (!fill_map(info, map, &player->h, all))
		return (0);
	info->slime = 0;
	info->fire = 0;
	info->o = 0;
	if (!check_close_map(map, info, all))
		return (0);
	print_map(map, info);
	return (1);
}
