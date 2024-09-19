/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:37:27 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/19 15:08:31 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	error_handling(int ac, char **av)
{
	if (ac != 2)
		return (0);
	if (ft_strncmp(av[1] + (ft_strlen(av[1]) - 4), ".ber", 4))
		return (0);
	return (1);
}
