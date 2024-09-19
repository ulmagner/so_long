/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:37:27 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/19 15:35:29 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	error_handling(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (0);
	if (ft_strncmp(av[1] + (ft_strlen(av[1]) - 4), ".ber", 4))
		return (0);
	fd = open(av[1], O_RDWR);
	if (fd < 0)
		return (ft_printf(2, "Error\nCarte can't be open\n"), 0);	
	return (1);
}
