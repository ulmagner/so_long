/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:11:03 by ulysse            #+#    #+#             */
/*   Updated: 2024/05/24 10:14:42 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_resultat_len(int nb)
{
	int	number_len;

	number_len = 0;
	if (nb < 0)
	{
		number_len++;
		nb *= -1;
		if (nb == -2147483648)
			return (11);
	}
	while (nb >= 10)
	{
		number_len++;
		nb /= 10;
	}
	return (number_len + 1);
}

static char	*itoa_convert(int *i, char *resultat, int n)
{
	unsigned int	res;

	if (n < 0)
	{
		resultat[(*i)++] = '-';
		res = -n;
	}
	else
		res = n;
	if (res >= 10)
		itoa_convert(i, resultat, res / 10);
	resultat[(*i)++] = res % 10 + '0';
	if (*i == ft_resultat_len(n))
		resultat[*i] = '\0';
	return (resultat);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*resultat;

	resultat = malloc(sizeof(char) * (ft_resultat_len(n) + 1));
	if (!resultat)
		return (NULL);
	i = 0;
	itoa_convert(&i, resultat, n);
	return (resultat);
}
