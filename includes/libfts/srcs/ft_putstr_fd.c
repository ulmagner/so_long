/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:37:14 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/17 16:53:46 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(const char *s, int *nbr, int fd)
{
	if (!s)
		s = "(null)";
	while (*s != '\0')
		ft_putchar_fd(*s++, nbr, fd);
}
