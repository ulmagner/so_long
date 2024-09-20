/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:01:31 by ulmagner          #+#    #+#             */
/*   Updated: 2024/05/23 16:36:19 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	char	*cpy_s;
	int		i;

	if (!s)
		return (NULL);
	cpy_s = malloc(sizeof(char) * (ft_strlen(s)+ 1));
	if (!cpy_s)
		return (NULL);
	i = -1;
	while (s[++i] != '\0')
		cpy_s[i] = f(i, s[i]);
	cpy_s[i] = '\0';
	return (cpy_s);
}
