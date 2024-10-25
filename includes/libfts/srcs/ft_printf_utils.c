/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:02:27 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/17 16:56:34 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putptr_printf(void *ptr, int *nbr, int output)
{
	unsigned long long	num;

	num = (unsigned long long)ptr;
	if (num == 0)
	{
		ft_putstr_fd("(nil)", nbr, output);
		return ;
	}
	ft_putstr_fd("0x", nbr, output);
	ft_putnbr_basep(num, "0123456789abcdef", nbr, output);
}

void	ft_putunbr_printf(unsigned int n, int *nbr, int output)
{
	if (n > 9)
		ft_putunbr_printf(n / 10, nbr, output);
	ft_putchar_fd((n % 10) + 48, nbr, output);
}

void	ft_putnbr_basep(unsigned long long n, char *base, int *nbr, int output)
{
	unsigned long long	res;
	unsigned int		base_len;

	base_len = ft_strlen(base);
	if (base_len <= 1)
		return ;
	res = n;
	if (res >= base_len)
		ft_putnbr_basep((res / base_len), base, nbr, output);
	ft_putchar_fd(base[res % base_len], nbr, output);
}

bool	is_flag(char c, const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}
