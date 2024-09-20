/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:13:41 by ulysse            #+#    #+#             */
/*   Updated: 2024/05/24 10:43:57 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	i = -1;
	while (src[++i] != '\0' && i < n)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return (dest);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	value;

	if (size == 0 && !dest)
		return (0);
	value = 0;
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	value = src_len + dest_len;
	if (!dest || !src)
		return (0);
	else if (size <= dest_len)
		return (src_len + size);
	dest = ft_strncat(dest, src, size - dest_len - 1);
	return (value);
}
