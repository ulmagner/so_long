/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:39:58 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/26 10:01:54 by ulmagner         ###   ########.fr       */
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
	if (info->path_texture)
		ft_tabfree(info->path_texture);
}

void	ft_freewindow(t_window *window)
{
	mlx_destroy_window(window->mlx, window->main);
	mlx_destroy_display(window->mlx);
	free(window->mlx);
}

void	ft_freeimage(t_solong *solong)
{
	int	i;
	int	j;

	i = -1;
	if (!solong->tileset || !*solong->tileset)
		return ;
	while (++i < solong->info.nbr_image)
	{
		j = -1;
		while (++j < solong->info.nbr_i[i])
		{
			mlx_destroy_image(solong->window.mlx, solong->tileset[i][j].img);
		}
		free(solong->tileset[i]);
	}
	free(solong->tileset);
	mlx_destroy_image(solong->window.mlx, solong->ground.img);
}

void	ft_freeplayer(t_player *player)
{
	free(player);
}

void	ft_clearall(t_solong *solong)
{
	ft_freemap(&solong->map);
	ft_freeimage(solong);
	ft_freeinfo(&solong->info);
	ft_freewindow(&solong->window);
	close(solong->info.fd);
}
