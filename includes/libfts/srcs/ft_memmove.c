/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:12:29 by ulysse            #+#    #+#             */
/*   Updated: 2024/05/23 01:12:30 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if ((char *)dest < (const char *)src)
		ft_memcpy(dest, src, n);
	else if ((char *)dest > (const char *)src)
	{
		while (n > 0)
		{
			*((char *)dest + (n - 1)) = *((char const *)src + (n - 1));
			n--;
		}
	}
	return (dest);
}
