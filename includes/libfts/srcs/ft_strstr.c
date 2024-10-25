/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:14:23 by ulysse            #+#    #+#             */
/*   Updated: 2024/05/23 17:05:11 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	n;
	size_t	little_len;

	i = -1;
	little_len = ft_strlen(needle);
	if (little_len == 0)
		return ((char *)haystack);
	while (haystack[++i] != '\0')
	{
		n = 0;
		while (haystack[i + n] == needle[n])
		{
			n++;
			if (n == little_len)
				return ((char *)&haystack[i]);
		}
	}
	return (NULL);
}
