/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:42:25 by ulmagner          #+#    #+#             */
/*   Updated: 2024/08/21 13:32:45 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	sub_len;

	if (!s)
		return (NULL);
	if ((int)start >= ft_strlen(s))
	{
		sub_str = malloc(1);
		if (!sub_str)
			return (NULL);
		sub_str[0] = '\0';
		return (sub_str);
	}
	sub_len = ft_strlen(s) - start;
	if (sub_len > len)
		sub_len = len;
	sub_str = malloc(sizeof(char) * (sub_len + 1));
	if (!sub_str)
		return (NULL);
	ft_strncpy(sub_str, s + start, sub_len);
	sub_str[sub_len] = '\0';
	return (sub_str);
}
