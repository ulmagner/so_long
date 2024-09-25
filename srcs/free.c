/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:39:58 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/25 19:08:03 by ulmagner         ###   ########.fr       */
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
}

void	ft_freewindow(t_window *window)
{
	free(window->mlx);
}

// void	ft_freeimage(t_solong **solong)
// {
// 	free((*solong)->coin);
// 	free((*solong)->wall);
// 	free((*solong)->deco);
// 	free((*solong)->floor);
// 	free((*solong)->exit);
// }

void	ft_freeplayer(t_player *player)
{
	free(player);
}

void	ft_clearall(t_solong *solong)
{
	int	i;

	i = -1;
	// mlx_destroy_image(solong->window.mlx, solong->floor[0].img);
	// while (++i < 4)
	// 	mlx_destroy_image(solong->window.mlx, solong->wall[i].img);
	// mlx_destroy_image(solong->window.mlx, solong->coin[0].img);
	// mlx_destroy_image(solong->window.mlx, solong->deco[0].img);
	// mlx_destroy_image(solong->window.mlx, solong->exit[0].img);
	// mlx_destroy_image(solong->window.mlx, solong->player.player[0].img);
	// mlx_destroy_image(solong->window.mlx, solong->ground.img);
	mlx_destroy_window(solong->window.mlx, solong->window.main);
	mlx_destroy_display(solong->window.mlx);
	ft_freemap(&solong->map);
	ft_freeinfo(&solong->info);
	ft_freewindow(&solong->window);
	ft_freeplayer(&solong->player);
	// ft_freeimage(&solong);
	close(solong->info.fd);
}
