/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:28:06 by ulmagner          #+#    #+#             */
/*   Updated: 2024/08/21 13:32:10 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_str(char const c, char const *set)
{
	while (*set != '\0')
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*cpy_s1;
	const char	*start;
	const char	*end;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	end = s1 + ft_strlen(s1);
	while (*start && is_in_str(*start, set))
		start++;
	while (end > start && is_in_str(*(end - 1), set))
		end--;
	cpy_s1 = malloc(sizeof(char) * (end - start + 1));
	if (!cpy_s1)
		return (NULL);
	ft_strncpy(cpy_s1, start, end - start);
	cpy_s1[end - start] = '\0';
	return (cpy_s1);
}
