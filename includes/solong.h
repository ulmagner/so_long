/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:04:39 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/09 19:49:45 by ulmagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef all_H
# define all_H

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
	char			i;
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
	int				(*deco)[2];
	int				fire;
	int				oeuil;
	int				ennemies;
	int				trap;
	int				coin;
	int				collectible;
	int				slime;
	bool			exit;
	int				fd;
	int				i_x;
	int				i_y;
	int				line;
	int				column;
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
	int		i;
	int		*animation;
	int		pv;
	int		ms;
	bool	is_dead;
	int		interaction[4][2];
	t_map	*h;
}	t_player;

typedef struct s_oeuil
{
	int		x;
	int		y;
	int		i;
	int		animation[3];
	int		pv;
	int		ms;
	bool	is_dead;
	bool	is_stun;
	int		anim;
	int		rd_dir;
	int		interaction[4][2];
	t_map	*o;
}	t_oeuil;

typedef struct s_wall
{
	int		i;
	int		anim;
}	t_wall;

typedef struct s_deco
{
	int		i;
	int		anim_jar;
	int		is_break;
	int		x_pxl;
	int		y_pxl;
}	t_deco;

typedef struct s_slime
{
	int		x;
	int		y;
	int		i;
	int		anim_slime;
	bool	is_free;
}	t_slime;

typedef struct s_trap
{
	int		x;
	int		y;
	int		curr_frame;
	int		tot_frame;
	int		i;
	int		anim_trap;
	bool	detect;
}	t_trap;

typedef struct s_movement
{
	bool	move[65535];
	int		keycode;
	bool	i_move[4];
}	t_movement;

typedef struct s_action
{
	int		curr_frame;
	int		tot_frame;
	int		x;
	int		y;
	bool	button;
	bool	is_action;
}	t_action;

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

typedef struct s_all
{
	t_window	window;
	t_info		info;
	t_player	player;
	t_oeuil		*oeuil;
	t_deco		deco;
	t_map		*map;
	t_image		***tileset;
	t_image		ground;
	t_image		game;
	t_movement	movement;
	t_action	attack;
	t_action	counter;
	t_random	random;
	t_wall		wall;
	t_slime		*slime;
	t_trap		*trap;
	int			i;
}	t_all;

t_map	**init_row_lst(t_info *info);
unsigned int	get_pixel_color(t_image *image, int x, int y);
int		check_hitbox_player(int interaction[4][2], t_player *player);
int		check_hitbox_oeuil(int interaction[4][2], t_oeuil *oeuil);
int		check_hitbox_jar(int interaction[4][2], t_info info);
void	dir_up(t_player *player, t_movement *movement, t_all *all);
void	dir_down(t_player *player, t_movement *movement, t_all *all);
void	dir_left(t_player *player, t_movement *movement, t_all *all);
void	dir_right(t_player *player, t_movement *movement, t_all *all);
void	ft_pixel_put(t_image *image, int x, int y, int color);
void	copy_oeuil_to_map(t_all *all, t_oeuil *oeuil);
void	copy_to_map(t_image *image, t_image *ground, t_map *map);
void	copy_ground_to_map(t_all *all);
void	copy_slime_to_map(t_all *all, t_slime *slime);
void	copy_player_to_map(t_all *all);
void	copy_trap_to_map(t_all *all, t_trap *trap);
void	ft_freeinfo(t_info *info);
void	ft_freeplayer(t_player *player);
void	ft_freemap(t_map **map);
void	ft_tabfree(char **tab);
void	ft_clearall(t_all *all);
void	build_map(t_all *all);
void	build_game(t_all *all);
void	chain_map(t_map **curr, t_map **head, t_map *node);
void	chain_map_updown(t_map *node, t_info *info, t_map **head, t_map **curr);
void	check_floor(char *line, t_info *info);
void	check_wall(char *line, t_info *info);
void	check_deco(char *line, t_info *info);
void	check_exit(char *line, t_info *info);
void	check_slime(char *line, t_info *info);
void	check_player(char *line, t_info *info);
void	check_ennemies(char *line, t_info *info);
void	check_trap(char *line, t_info *info);
int		get_hitbox_player(t_player *player);
int		get_hitbox_oeuil(t_oeuil *oeuil);
int		trap_handling(t_all *all, t_trap *trap);
int		slime_handling(t_all *all, t_slime *slime);
int		get_randoms(int min, int max, int count);
int		split_tileset(t_all *all, t_info *info);
int		get_paths(char *file, t_info *info);
int		launcher(t_all *all, char **av);
int		movement_p(int keycode, t_all *all);
int		movement_r(int keycode, t_all *all);
int		movement_handling_oeuil(t_all *all, t_oeuil *oeuil);
int		movement_handling(t_all *all);
int		action_p(int button, int x, int y, t_all *all);
int		action_r(int button, int x, int y, t_all *all);
int		action_handling(t_all *all);
int		get_map(t_info *info, int *line, int *column);
int		check_ep_doubles(t_info *info);
int		check_close_map(t_map **map, t_info *info, t_player **player, t_all *all);
int		make_list(t_info *info, int *i, t_map **node, t_map **h, t_all *all);
int		empty_string(t_info *info);
int		map_handling(t_info *info, t_map **map, t_player *player, t_all *all);
int		error_handling(int ac, char **av, t_info *info);
int		main(int ac, char **av);
#endif //all_H