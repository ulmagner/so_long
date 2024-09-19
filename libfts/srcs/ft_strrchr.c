/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:14:18 by ulysse            #+#    #+#             */
/*   Updated: 2024/05/23 01:14:19 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_occ;
	int			i;

	i = 0;
	last_occ = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			last_occ = &s[i];
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	return ((char *)last_occ);
}
