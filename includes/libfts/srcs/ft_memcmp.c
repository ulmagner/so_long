/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:12:14 by ulysse            #+#    #+#             */
/*   Updated: 2024/09/18 21:36:01 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s;
	unsigned char	*p;
	size_t			i;

	s = (unsigned char *)s1;
	p = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s[i] != p[i])
			return (s[i] - p[i]);
		i++;
	}
	return (0);
}
