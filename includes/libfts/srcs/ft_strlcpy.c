/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:13:45 by ulysse            #+#    #+#             */
/*   Updated: 2024/08/21 13:32:33 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size > 0)
	{
		if (src_len >= size)
		{
			ft_strncpy(dest, src, size - 1);
			dest[size - 1] = '\0';
		}
		else
			ft_strncpy(dest, src, src_len + 1);
	}
	return (src_len);
}
