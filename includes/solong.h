/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:04:39 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/19 15:29:29 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"
// # include "./minilibx-linux/mlx.h"

typedef struct s_map
{
	char **map;
}	t_map;

typedef struct s_lst
{
	char			*path;
	char			**argvec;
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_lst;

int	map_handling(t_map *map);
int	error_handling(int ac, char **av);
int		main(int ac, char **av);
#endif //SOLONG_H