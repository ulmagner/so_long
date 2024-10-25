/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:11:23 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/17 16:57:39 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	printf_converted(va_list args, char c, int *nbr, int output)
{
	if (c == '%')
		ft_putchar(c, nbr);
	else if (c == 'c')
		ft_putchar_fd(va_arg(args, int), nbr, output);
	else if (c == 's')
		ft_putstr_fd(va_arg(args, const char *), nbr, output);
	else if (c == 'd' || c == 'i')
		ft_putnbr_fd(va_arg(args, int), nbr, output);
	else if (c == 'u')
		ft_putunbr_printf(va_arg(args, unsigned int), nbr, output);
	else if (c == 'x')
		ft_putnbr_basep(va_arg(args, unsigned int),
			"0123456789abcdef", nbr, output);
	else if (c == 'p')
		ft_putptr_printf(va_arg(args, void *), nbr, output);
	else if (c == 'X')
		ft_putnbr_basep(va_arg(args, unsigned int),
			"0123456789ABCDEF", nbr, output);
}

int	ft_printf(int output, const char *str, ...)
{
	int			i;
	int			nbr_printed_char;
	va_list		args;

	i = -1;
	nbr_printed_char = 0;
	va_start(args, str);
	while (str[++i] != '\0')
	{
		if (str[i] == '%')
		{
			if (is_flag(str[++i], "# +-"))
			{
				if (is_flag(str[i], "cspdiuxX%%"))
					printf_converted(args, str[i], &nbr_printed_char, output);
			}
			else if (is_flag(str[i], "cspdiuxX%%"))
				printf_converted(args, str[i], &nbr_printed_char, output);
		}
		else
			ft_putchar_fd(str[i], &nbr_printed_char, output);
	}
	return (va_end(args), nbr_printed_char);
}
