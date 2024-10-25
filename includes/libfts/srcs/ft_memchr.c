/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:12:10 by ulysse            #+#    #+#             */
/*   Updated: 2024/05/23 01:12:10 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		if (*((const unsigned char *)s + i) == (unsigned char)c)
			return ((void *)s + i);
	if (c == '\0' && i < n)
		return ((void *)s);
	return (NULL);
}
