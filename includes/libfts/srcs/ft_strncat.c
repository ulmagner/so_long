/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:14:02 by ulysse            #+#    #+#             */
/*   Updated: 2024/05/23 01:14:02 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
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
