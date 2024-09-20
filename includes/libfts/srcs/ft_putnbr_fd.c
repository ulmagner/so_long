/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:43:49 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/17 16:48:08 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int *nbr, int fd)
{
	if (n < 0)
	{
		if (n == INT_MIN)
		{
			ft_putstr_fd("-2147483648", nbr, fd);
			return ;
		}
		else
		{
			n *= -1;
			ft_putchar_fd('-', nbr, fd);
		}
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, nbr, fd);
	ft_putchar_fd((n % 10) + 48, nbr, fd);
}
