/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:39:58 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/25 11:28:46 by ulmagner         ###   ########.fr       */
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

void	ft_mapfree(t_map **map)
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
}

void	ft_freewindow(t_window *window)
{
	free(window->mlx);
}

void	ft_clearall(t_solong *solong)
{
	mlx_destroy_image(solong->window.mlx, solong->tileset.img);
	mlx_destroy_image(solong->window.mlx, solong->ground.img);
	mlx_destroy_window(solong->window.mlx, solong->window.main);
	mlx_destroy_display(solong->window.mlx);
	ft_mapfree(&solong->map);
	ft_freeinfo(&solong->info);
	ft_freewindow(&solong->window);
	close(solong->info.fd);
}
