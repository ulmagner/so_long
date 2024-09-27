/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:04:39 by ulmagner          #+#    #+#             */
/*   Updated: 2024/09/27 15:22:13 by ulmagner         ###   ########.fr       */
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
# ifndef MANDATORY
#  define MANDATORY 0
# else
# define MANDATORY 1
# endif

typedef struct s_map
{
	char			index;
	int				x;
	int				y;
	int				x_pxl;
	int				y_pxl;
	int				is_visited;
	struct s_map	*right;
	struct s_map	*left;
	struct s_map	*up;
	struct s_map	*down;
	struct s_map	*player;
}	t_map;

typedef struct s_info
{
	int				coin;
	bool			exit;
	int				fd;
	int				i_x;
	int				i_y;
	int				nbr_line;
	int				nbr_column;
	int				size_map;
	char			*map;
	int				nbr_image;
	int				*nbr_i;
	int				*nbr_a;
	char			**path_texture;
}	t_info;

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

typedef struct s_player
{
	int		x;
	int		y;
	int		index_n;
	int		index_s;
	int		index_e;
	int		index_o;
	int		index;
	int		*animation;
	t_map	*hero;
}	t_player;

typedef struct s_movement
{
	bool	move[65535];
	int		keycode;
}	t_movement;

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
	t_image		***tileset;
	t_image		ground;
	t_movement	movement;
	int			i;
}	t_solong;

t_map	**init_row_lst(t_info *info);
t_image	***split_tileset(t_solong *solong);
int		get_paths(char *file, t_info *info);
unsigned int	get_pixel_color(t_image *image, int x, int y);
void	ft_pixel_put(t_image *image, int x, int y, int color);
void	copy_player_to_map(t_solong *solong, int index);
void	ft_freeinfo(t_info *info);
void	ft_freeplayer(t_player *player);
void	ft_freemap(t_map **map);
void	ft_tabfree(char **tab);
void	ft_clearall(t_solong *solong);
void	build_map(t_solong *solong);
void	chain_map(t_map **curr, t_map **head, t_map *node);
void	chain_map_updown(t_map *node, t_info *info, t_map **head, t_map **curr);
int		launcher(t_solong *solong, char **av);
int		movement_p(int keycode, t_solong *solong);
int		movement_r(int keycode, t_solong *solong);
int		movement_handling(t_solong *solong);
int		get_map(t_info *info, int *nbr_line, int *nbr_column);
int		check_ep_doubles(t_info *info);
int		check_close_map(t_map **map, t_info *info, t_player **player);
int		make_list(t_info *info, int *i, t_map **node, t_map **hero);
int		empty_string(t_info *info);
int		map_handling(t_info *info, t_map **map, t_player *player);
int		error_handling(int ac, char **av, t_info *info);
int		main(int ac, char **av);
#endif //SOLONG_H