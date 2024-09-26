/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:13:03 by ulysse            #+#    #+#             */
/*   Updated: 2024/09/26 09:53:40 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**spliting(char **split, char *str, int nbr_words, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < nbr_words)
	{
		while (str[j] && str[j] == c)
			j++;
		k = j;
		while (str[j] && str[j] != c)
			j++;
		split[i] = malloc(sizeof(char) * ((j - k) + 1));
		if (!split[i])
		{
			while (i > 0)
				free(split[--i]);
			return (free(split), NULL);
		}
		ft_strncpy(split[i], &str[k], (j - k));
		split[i++][j - k] = '\0';
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(char *str, char c)
{
	char	**split;
	int		nbr_words;

	if (!str)
		return (NULL);
	nbr_words = ft_countwords(str, c);
	split = malloc(sizeof(char *) * (nbr_words + 1));
	if (!split)
		return (NULL);
	split = spliting(split, str, nbr_words, c);
	return (split);
}
