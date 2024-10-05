/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:04:39 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/05 21:31:35 by ulysse           ###   ########.fr       */
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
	int				collectible;
	int				slime;
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
	int		index;
	int		*animation;
	int		pv;
	int		ms;
	t_map	*hero;
}	t_player;

typedef struct s_oeuil
{
	int		x;
	int		y;
	int		index;
	int		*animation;
	int		pv;
	int		ms;
	t_map	*o;
}	t_oeuil;

typedef struct s_wall
{
	int		index;
	int		anim;
}	t_wall;

typedef struct s_deco
{
	int		index;
	int		anim_jar;
	int		is_break;
}	t_deco;

typedef struct s_slime
{
	int		x;
	int		y;
	int		index;
	int		anim_slime;
	int		is_free;
}	t_slime;

typedef struct s_movement
{
	bool	move[65535];
	int		keycode;
	bool	index_move[4];
}	t_movement;

typedef struct s_attack
{
	bool	attack[4];
	int		current_frame;
	int		total_frame;
	int		x;
	int		y;
	int		button;
	bool	is_attack;
}	t_attack;

typedef struct s_window
{
	void	*mlx;
	void	*main;
	int		main_width;
	int		main_height;
}	t_window;

typedef struct s_random
{
	int	rd_floor;
}	t_random;

typedef struct s_solong
{
	t_window	window;
	t_info		info;
	t_player	player;
	t_oeuil		oeuil;
	t_deco		deco;
	t_map		*map;
	t_image		***tileset;
	t_image		ground;
	t_image		game;
	t_movement	movement;
	t_attack	attack;
	t_random	random;
	t_wall		wall;
	t_slime		*slime;
	int			i;
}	t_solong;

t_map	**init_row_lst(t_info *info);
unsigned int	get_pixel_color(t_image *image, int x, int y);
void	dir_up(t_player *player, t_movement *movement, t_solong *solong);
void	dir_down(t_player *player, t_movement *movement, t_solong *solong);
void	dir_left(t_player *player, t_movement *movement, t_solong *solong);
void	dir_right(t_player *player, t_movement *movement, t_solong *solong);
void	ft_pixel_put(t_image *image, int x, int y, int color);
void	copy_oeuil_to_map(t_solong *solong);
void	copy_tile_to_map(t_image *image, t_image *ground, t_map *map);
void	copy_ground_to_map(t_solong *solong);
void	copy_slime_to_map(t_solong *solong, t_slime *slime);
void	copy_player_to_map(t_solong *solong);
void	ft_freeinfo(t_info *info);
void	ft_freeplayer(t_player *player);
void	ft_freemap(t_map **map);
void	ft_tabfree(char **tab);
void	ft_clearall(t_solong *solong);
void	build_map(t_solong *solong);
void	build_game(t_solong *solong);
void	chain_map(t_map **curr, t_map **head, t_map *node);
void	chain_map_updown(t_map *node, t_info *info, t_map **head, t_map **curr);
int		get_randoms(int min, int max, int count);
int		split_tileset(t_solong *solong, t_info *info);
int		get_paths(char *file, t_info *info);
int		launcher(t_solong *solong, char **av);
int		movement_p(int keycode, t_solong *solong);
int		movement_r(int keycode, t_solong *solong);
int		movement_handling(t_solong *solong);
int		attack_p(int button, int x, int y, t_solong *solong);
int		attack_r(int button, int x, int y, t_solong *solong);
int		attack_handling(t_solong *solong, t_player *player);
int		get_map(t_info *info, int *nbr_line, int *nbr_column);
int		check_ep_doubles(t_info *info);
int		check_close_map(t_map **map, t_info *info, t_player **player, t_oeuil **oeuil);
int		make_list(t_info *info, int *i, t_map **node, t_map **hero, t_map **o);
int		empty_string(t_info *info);
int		map_handling(t_info *info, t_map **map, t_player *player, t_oeuil *oeuil);
int		error_handling(int ac, char **av, t_info *info);
int		main(int ac, char **av);
#endif //SOLONG_H