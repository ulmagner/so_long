/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:14:20 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/24 05:05:58 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	close_mlx(int keycode, t_solong *solong)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(solong->window.mlx, solong->window.main);
		mlx_destroy_display(solong->window.mlx);
		exit((ft_clearall(solong), EXIT_SUCCESS));
	}
	return (0);
}

int	launcher(t_solong *solong)
{
	solong->window.mlx = mlx_init();
	solong->window.main = mlx_new_window(solong->window.mlx, \
		1920, 1080, "Hello world!");
	mlx_hook(solong->window.main, 2, 1L << 0, close_mlx, solong);
	mlx_loop(solong->window.mlx);
	return (1);
}

int	main(int ac, char **av)
{
	t_solong	solong;

	solong = (t_solong){0};
	if (!error_handling(ac, av, &solong.info))
		return (EXIT_FAILURE);
	if (!map_handling(&solong.info, &solong.map, &solong.player))
		return (ft_clearall(&solong), EXIT_FAILURE);
	if (!launcher(&solong))
		return (ft_clearall(&solong), EXIT_FAILURE);
	if (close(solong.info.fd) == -1)
		return (ft_clearall(&solong), EXIT_FAILURE);
	return (ft_clearall(&solong), EXIT_SUCCESS);
}
