/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:10:59 by ulysse            #+#    #+#             */
/*   Updated: 2024/09/19 17:39:09 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isstrchr(const char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}