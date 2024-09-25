/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:04:39 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/25 11:17:49 by ulmagner         ###   ########.fr       */
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
# include "mlx.h"
# include <X11/keysym.h>
# define TILE_SIZE 64

typedef struct s_map
{
	char			index;
	int				x;
	int				y;
	int				is_visited;
	struct s_map	*right;
	struct s_map	*left;
	struct s_map	*up;
	struct s_map	*down;
}	t_map;

typedef struct s_info
{
	int				coin;
	int				fd;
	int				i_x;
	int				i_y;
	int				nbr_line;
	int				nbr_column;
	int				size_map;
	char			*map;
}	t_info;

typedef struct s_player
{
	int	x;
	int	y;
}	t_player;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*img_path;
	int		width;
	int		height;
}	t_image;

typedef struct s_window
{
	void	*mlx;
	void	*main;
	int		main_width;
	int		main_height;
}	t_window;

typedef struct s_solong
{
	t_window	window;
	t_info		info;
	t_player	player;
	t_map		*map;
	t_image		tileset;
	t_image		ground;
}	t_solong;

t_map	**init_row_lst(t_info *info);
void	build_map(t_solong *solong);
void	ft_clearall(t_solong *solong);
void	chain_map(t_map **curr, t_map **head, t_map *node);
void	chain_map_updown(t_map *node, t_info *info, t_map **head, t_map **curr);
int		get_map(t_info *info, int *nbr_line, int *nbr_column);
int		check_ep_doubles(t_info *info);
int		check_close_map(t_map **map, t_info *info, t_player *player);
int		make_list(t_info *info, int *i, t_map **node);
int		empty_string(t_info *info);
int		map_handling(t_info *info, t_map **map, t_player *player);
int		error_handling(int ac, char **av, t_info *info);
int		main(int ac, char **av);
#endif //SOLONG_H