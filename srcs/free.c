/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:39:58 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 16:21:48 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	ft_tabfree(char **tab)
{
	int	i;

	i = -1;
	if (!tab || !*tab)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	ft_freemap(t_map **map)
{
	t_map	*head;
	t_map	*curr;
	t_map	*next;

	if (!*map || !map)
		return ;
	head = *map;
	curr = head;
	while (curr != NULL)
	{
		next = curr->right;
		free(curr);
		curr = next;
		if (curr == head)
			break ;
	}
	*map = NULL;
}

void	ft_freeinfo(t_info *info)
{
	if (info->map)
		free(info->map);
	if (info->nbr_i)
		free(info->nbr_i);
	if (info->nbr_a)
		free(info->nbr_a);
	if (info->path_texture)
		ft_tabfree(info->path_texture);
	if (info->deco)
		free(info->deco);
}

void	ft_freeplayer(t_player *player)
{
	if (player->animation)
		free(player->animation);
}

void	ft_freeoeuil(t_oeuil **oeuil)
{
	free(*oeuil);
}

void	ft_freeslime(t_solong *solong)
{
	free(solong->slime);
}

void	ft_freestrap(t_solong *solong)
{
	free(solong->trap);
}
