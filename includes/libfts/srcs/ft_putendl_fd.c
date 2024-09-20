/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:49:23 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/17 16:52:07 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int *nbr, int fd)
{
	if (!s)
		return ;
	while (*s != '\0')
		ft_putchar_fd(*s++, nbr, fd);
	ft_putchar_fd('\n', nbr, fd);
}
