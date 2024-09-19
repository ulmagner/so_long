/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:12:05 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/18 22:18:41 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_rest_of_line(char *tmp, char *line)
{
	int	i;

	i = 0;
	while (tmp[i] != '\0')
	{
		if (tmp[i] == '\n')
		{
			i++;
			ft_strcpy(line, &tmp[i]);
			tmp[i] = '\0';
			break ;
		}
		i++;
	}
	return (tmp);
}

static char	*read_till_newline(char *tmp, int fd, char *line)
{
	char	*scnd;
	ssize_t	bytes_read;

	bytes_read = read(fd, line, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		line[bytes_read] = '\0';
		scnd = ft_strjoin(tmp, line);
		if (!scnd)
			return (free(tmp), NULL);
		free(tmp);
		tmp = scnd;
		if (ft_strchr(tmp, '\n'))
			break ;
		bytes_read = read(fd, line, BUFFER_SIZE);
	}
	if (bytes_read <= 0 && *tmp == '\0')
		return (free(tmp), NULL);
	line[0] = '\0';
	return (tmp);
}

static char	*manage_stat_if_not_null(char *tmp, char *line)
{
	char	*sub;

	sub = tmp;
	tmp = ft_strdup(line);
	if (!tmp)
		return (NULL);
	free(sub);
	line[0] = '\0';
	return (tmp);
}

char	*ft_get_next_line(int fd)
{
	static char	line[514][BUFFER_SIZE + 1] = {0};
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE == 0 || fd > 514)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		line[fd][0] = '\0';
		return (NULL);
	}
	tmp = malloc(sizeof(char) * 1);
	if (!tmp)
		return (NULL);
	*tmp = '\0';
	if (line[fd][0] != '\0')
		tmp = manage_stat_if_not_null(tmp, line[fd]);
	tmp = read_till_newline(tmp, fd, line[fd]);
	if (tmp)
		tmp = get_rest_of_line(tmp, line[fd]);
	return (tmp);
}
