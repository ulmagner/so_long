/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:10:31 by ulysse            #+#    #+#             */
/*   Updated: 2024/05/24 10:34:17 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countwords(char *str, char c)
{
	int	count;
	int	i;
	int	is_word;

	count = 0;
	i = 0;
	is_word = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && !is_word)
		{
			count++;
			is_word = 1;
		}
		else if (str[i] == c)
			is_word = 0;
		i++;
	}
	return (count);
}
