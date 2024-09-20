/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:04:39 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/20 17:22:47 by ulmagner         ###   ########.fr       */
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

typedef struct s_info
{
	int		fd;
	int		i_x;
	int		i_y;
	int		nbr_line;
	int		nbr_column;
	int		size_map;
	struct s_map	**row;
	char	*map;
}	t_info;

typedef struct s_map
{
	char			index;
	int				x;
	int				y;
	struct s_map	*right;
	struct s_map	*left;
	struct s_map	*up;
	struct s_map	*down;
}	t_map;

t_map	**init_row_lst(t_info *info);
void	ft_freeall(t_info *info, t_map **map);
int		empty_string(t_info *info);
int		fill_map(t_info *info, t_map **head);
int		map_handling(t_info *info, t_map **map);
int		error_handling(int ac, char **av, t_info *info);
int		main(int ac, char **av);
#endif //SOLONG_H