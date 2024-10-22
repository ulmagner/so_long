/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:14:20 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/18 19:34:54 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	get_randoms(int min, int max, int count)
{
	int	i;
	int	rd_num;

	i = -1;
	rd_num = -1;
	while (++i < count)
		rd_num = rand() % (max - min + 1) + min;
	return (rd_num);
}

int	launch_lvl(t_all *all, int ac, char **av, int lvl)
{
	*all = (t_all){0};
	all->lvl = lvl + 1;
	all->ac = ac;
	all->av = av;
	if (!error_handling(ac, av, &all->info, all->lvl))
		return (0);
	if (!get_paths(av[ac - 1], &all->info))
		return (0);
	if (!map_handling(&all->info, &all->map, &all->player, all))
		return (0);
	if (!launcher(all))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_all	all;

	all = (t_all){0};
	if (!launch_lvl(&all, ac, av, all.lvl))
		return (ft_clearall(&all), EXIT_FAILURE);
	return (ft_clearall(&all), EXIT_SUCCESS);
}
