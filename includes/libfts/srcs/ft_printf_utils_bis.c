/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:03:02 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 19:08:57 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_blank(int blank, int *nbr)
{
	int	i;

	i = 0;
	while (i < blank)
	{
		ft_putchar(' ', nbr);
		i++;
	}
}

int	minus_flag(const char *str, int *i)
{
	char	*atoint;
	int		c;
	int		atointed;

	c = 0;
	atointed = 0;
	while (!is_flag(str[*i + c], "cspdiuxX%%"))
	{
		c++;
	}
	atoint = malloc(sizeof(char) * (c + 1));
	if (!atoint)
		return (0);
	c = 0;
	while (!is_flag(str[*i], "cspdiuxX%%"))
	{
		atoint[c++] = str[*i];
		(*i)++;
	}
	atoint[c] = '\0';
	atointed = ft_atoi(atoint);
	return (free(atoint), atointed);
}

int	printf_bonus_converted(const char *str, int *i, int *nbr)
{
	int	atointed;

	atointed = 0;
	if (str[*i] == ' ')
		ft_putchar(' ', nbr);
	if (str[*i] == '+')
		ft_putchar('+', nbr);
	if (str[*i] == '#')
		ft_putchar('0', nbr);
	if (str[*i] == '-')
	{
		(*i)++;
		atointed = minus_flag(str, i);
	}
	return (atointed);
}

void	ft_putchar(char c, int *nbr)
{
	write(((*nbr)++, 1), &c, 1);
}

void	ft_putstr(const char *s, int *nbr, int *blank)
{
	if (!s)
		s = "(null)";
	while (*s != '\0')
	{
		ft_putchar(*s++, nbr);
		(*blank)--;
	}
}
