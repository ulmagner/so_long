/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:10:26 by ulysse            #+#    #+#             */
/*   Updated: 2024/05/23 01:10:27 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*c_alloc;
	size_t	bytes_allocated;

	bytes_allocated = nmemb * size;
	if (nmemb != 0 && size > INT_MAX / nmemb)
		return (NULL);
	if (nmemb == 0 || size == 0)
	{
		c_alloc = malloc(1);
		if (!c_alloc)
			return (NULL);
		ft_bzero(c_alloc, 1);
		return (c_alloc);
	}
	c_alloc = malloc(bytes_allocated);
	if (!c_alloc)
		return (NULL);
	ft_bzero(c_alloc, bytes_allocated);
	return (c_alloc);
}
