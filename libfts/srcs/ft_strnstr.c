/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:57:56 by ulmagner          #+#    #+#             */
/*   Updated: 2024/05/23 16:30:06 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;
	size_t	little_len;

	if (!big && len == 0)
		return (NULL);
	i = -1;
	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	while (big[++i] != '\0' && i < len)
	{
		n = 0;
		while (big[i + n] == little[n] && ((i + little_len) <= len))
		{
			n++;
			if (n == little_len)
				return ((char *)&big[i]);
		}
	}
	return (NULL);
}
