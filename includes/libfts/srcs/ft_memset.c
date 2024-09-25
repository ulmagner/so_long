/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:12:35 by ulysse            #+#    #+#             */
/*   Updated: 2024/09/25 19:36:43 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned int	*ptr_s;

	ptr_s = (unsigned int *)s;
	i = -1;
	while (++i < n)
		ptr_s[i] = (unsigned int)c;
	return (s);
}
