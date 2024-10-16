/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulmagner <ulmagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:33:56 by ulmagner          #+#    #+#             */
/*   Updated: 2024/10/16 16:57:34 by ulmagner         ###   ########.fr       */
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
# include <math.h>
# include "libft.h"
# include "mlx.h"
# include <X11/keysym.h>
# define TILE_SIZE 64
# ifndef MANDATORY
#  define MANDATORY 0
# else
#  define MANDATORY 1
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
	int				fire;
	int				oeil;
	int				ennemies;
	int				trap;
	int				coin;
	int				collectible;
	int				slime;
	bool			exit;
	int				exit_x;
	int				exit_y;
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
	int		w;
	int		h;
}	t_image;

typedef struct s_player
{
	int		x;
	int		y;
	int		i;
	int		*animation;
	int		pv;
	int		ms;
	float	r;
	bool	is_dead;
	int		interaction[4][2];
	t_map	*h;
}	t_player;

typedef struct s_oeil
{
	int		x;
	int		y;
	int		i;
	int		animation[3];
	int		pv;
	int		ms;
	float	r;
	bool	is_dead;
	bool	is_stun;
	int		anim;
	int		rd_dir;
	int		interaction[4][2];
	int		reach;
	bool	focus;
	t_map	*o;
	int 	frameoeil;
	int		frameoeill;
}	t_oeil;

typedef struct s_wall
{
	int		i;
	int		anim;
}	t_wall;

typedef struct s_slime
{
	int		x;
	int		y;
	int		i;
	int		anim_slime;
	float	r;
	bool	is_free;
	t_map	*c;
	int		frameslime;
}	t_slime;

typedef struct s_trap
{
	int		x;
	int		y;
	int		curr_frame;
	int		tot_frame;
	int		i;
	float	r;
	int		anim_trap;
	bool	detect;
	t_map	*t;
	int		frametrap;
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
	int		main_w;
	int		main_h;
}	t_window;

typedef struct s_color
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_distance
{
	float	*p_o;
	float	*p_c;
	float	*p_t;
	float	p_e;
	float	p_f;
}	t_distance;

typedef struct s_random
{
	int	rd_floor;
}	t_random;

typedef struct s_view
{
	int	w;
	int	h;
	int	x;
	int	y;
	int	off_px;
	int	off_py;
}	t_view;

typedef struct s_fail
{
	int	a;
	int	b;
	int	k;
	int	j;
	int	i;
}	t_fail;

typedef struct s_all
{
	t_window	window;
	t_info		info;
	t_player	player;
	t_oeil		*oeil;
	t_map		*map;
	t_image		***tile;
	t_image		ground;
	t_image		plan;
	t_image		game;
	t_movement	movement;
	t_action	attack;
	t_action	counter;
	t_random	random;
	t_wall		wall;
	t_slime		*slime;
	t_trap		*trap;
	t_color		argb;
	t_distance	dist;
	t_view		view;
	t_fail		fail;
	int			i;
	int			frame;
	int			frameplayer;
	int			step;
}	t_all;

t_map			**init_row_lst(t_info *info);
int				set_view_to_ppos(t_view *view, t_player *player, t_all *all);
int				init_view(t_all *all, t_view *view);
int				init_window(t_all *all, char **av);
int				init_bg(t_image *ground, t_image *plan, t_all *all,
					t_window *window);
int				init_game(t_image *game, t_window *window, t_all *all);
unsigned int	get_pixel_color(t_image *image, int x, int y);
float			calculate_distance(t_player *player, float obj_x, float obj_y,
					int off);
int				calcul_dist(t_all *all);
int				init_distances(t_all *all);
void			copy_fog_plan(t_all *all);
void			dir_up(t_player *player, t_movement *movement, t_all *all);
void			dir_down(t_player *player, t_movement *movement, t_all *all);
void			dir_left(t_player *player, t_movement *movement, t_all *all);
void			dir_right(t_player *player, t_movement *movement, t_all *all);
void			ft_pixel_put(t_image *image, int x, int y, int color);
void			copy_to_game(t_image *image, t_image *ground, int x_ref,
					int y_ref);
void			copy_to_view(t_image *image, t_image *bg, t_view *view,
					t_all *all);
void			copy_oeil_plan(t_all *all, t_oeil *oeil);
void			copy_to_ground(t_image *image, t_image *ground, t_map *map);
void			copy_plan_to_game(t_all *all);
void			copy_ground_plan(t_all *all);
void			copy_slime_plan(t_all *all, t_slime *slime);
void			copy_player_plan(t_all *all);
void			copy_trap_plan(t_all *all, t_trap *trap);
void			ft_freeinfo(t_info *info);
void			ft_freeplayer(t_player *player);
void			ft_freemap(t_map **map);
void			ft_tabfree(char **tab);
void			ft_clearall(t_all *all);
void			build_minimap(t_all *all, t_image ***tile, t_image *plan);
void			build_ground(t_all *all);
void			build_plan(t_all *all);
void			chain_map(t_map **curr, t_map **head, t_map *node);
void			chain_map_updown(t_map *node, t_info *info, t_map **head,
					t_map **curr);
void			check_plan(char *line, t_info *info);
void			check_floor(char *line, t_info *info);
void			check_wall(char *line, t_info *info);
void			check_deco(char *line, t_info *info);
void			check_exit(char *line, t_info *info);
void			check_slime(char *line, t_info *info);
void			check_player(char *line, t_info *info);
void			check_ennemies(char *line, t_info *info);
void			check_trap(char *line, t_info *info);
int				trap_handling(t_all *all, t_trap *trap, int i);
int				slime_handling(t_all *all, t_slime *slime);
int				get_randoms(int min, int max, int count);
int				split_tile(t_all *all, t_info *info, t_fail *fail);
int				get_paths(char *file, t_info *info);
int				launcher(t_all *all, char **av);
int				movement_p(int keycode, t_all *all);
int				movement_r(int keycode, t_all *all);
int				movement_handling_oeil(t_all *all, t_oeil *oeil, int i);
int				movement_handling(t_all *all);
int				action_p(int button, int x, int y, t_all *all);
int				action_r(int button, int x, int y, t_all *all);
int				action_handling(t_all *all);
int				get_map(t_info *info, int *line, int *column);
int				check_ep_doubles(t_info *info);
int				check_close_map(t_map **map, t_info *info, t_all *all);
int				make_list(t_info *info, int *i, t_map **node, t_map **h,
					t_all *all);
int				empty_string(t_info *info);
int				map_handling(t_info *info, t_map **map, t_player *player,
					t_all *all);
int				error_handling(int ac, char **av, t_info *info);
int				main(int ac, char **av);
#endif //SOLONG_H