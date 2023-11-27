/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:06:09 by museker           #+#    #+#             */
/*   Updated: 2023/11/27 11:48:07 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

# define MOVE_SPEED 1
# define ROT_SPEED 1
# define FRAME_PER_SEC 2
# define PIX 16
# define SCREENWIDTH 800
# define SCREENHEIGHT 800

typedef struct s_ch
{
	double			ch_pos[3];

	double			cam_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			deltadist_x;
	double			deltadist_y;
	double			sidedist_x;
	double			sidedist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side1;
	double			wall_dist;

	int				side2;
	int				tex_x;
	int				line_h;
	int				draw_start;
	int				draw_end;

	void			*img_ptr;
	int				bpp;
	int				size_l;
	int				endian;
	unsigned int	*data;

	int				**tmp;
	int				*texture[4];

	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			pln_x;
	double			pln_y;

	int				fl;
	int				ce;
	int				h;
	int				w;
}					t_ch;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*north_wall;
	void			*west_wall;
	void			*south_wall;
	void			*east_wall;
	void			*sky;
	void			*floor;
}					t_game;

typedef struct s_data
{
	char			**all_map;
	char			**map;
	char			**redirect;
	char			***r_paths;
	int				file_width;
	int				file_height;
	int				map_width;
	int				map_height;
	int				win_width;
	int				win_height;
	int				map_location;
	int				*f;
	int				*c;
	t_game			g;
	t_ch			*ch;
}					t_data;

// ---------------------------  main.c  ----------------------------//
void				mlx_define(t_data *data);
void				ft_init(t_data *data, char *address);

// ---------------------  parser/check_map_utils.c  ---------------------//
int					ft_strlen_one_zero_map(t_data *data, char **s);
int					ft_check_one_zero_map_2(t_data *d, int i, int j);
void				print_double_pointer(char **str);
int					map_size(char **s);

// ---------------------  parser/check_map.c  ---------------------//
void				ft_error(char *str, int i, int j);
void				ft_check_one_zero_map(t_data *d);
int					ft_check_redirects2(t_data *d, int i);
void				ft_check_redirects(t_data *d);
void				ft_checkmap(t_data *data);

// ---------------------  parser/check_map2.c  ---------------------//
void				is_connected_map(t_data *d);
void				check_player2(t_data *d, int i, int j);
void				check_player(t_data *d);
int					get_value_redirect(t_data *d, char *redirect);

// ---------------------  parser/chec_redirect.c  ---------------------//
void				split_c(t_data *d, int i);
void				split_f(t_data *d, int i);
void				split_color_code(t_data *d);
void				check_value_of_redirect(char ***s);
void				ft_checkdirect(t_data *data);

// ---------------------  parser/chec_redirect2.c  ---------------------//
void				two_pointer_free(char **s);
int					two_pointer_size(char **s);
int					two_pointer_character_size(char **s);
char				*two_pointer_to_one_pointer(char **str);
void				split_direct(t_data *d);

// ---------------------  parser/get_map.c  ---------------------//
void				get_all_map_size(t_data *data, char *address);
void				set_redirects(t_data *data);
void				ft_getmap(t_data *d, int i);
void				ft_getmap2(t_data *d, int *i, int *j, int *k);
void				get_all_map(t_data *data, char *address);

// ---------------------  raycasting/floor.c  ---------------------//
int					calc_color(int color, int rgb);
void				set_color(int *texture, int *c_or_f);

// ---------------------  raycasting/init.c  ---------------------//
void				init_cub3d(t_ch *c);
void				init_vec(t_ch *v, char c, int x, int y);
void				init_texture(t_data *d);
void				init_tmp(t_ch *m);
void				init_mlx(t_data *d);

// ---------------------  raycasting/move.c  ---------------------//
void				rotate(t_ch *v, int opt);
void				move_ws(t_data *d, double opt);
void				move_ad(t_data *d, double opt);
int					close_win(t_data *d);
int					key_code(int keycode, t_data *d);

// ---------------------  raycasting/raycast.c  ---------------------//
void				init_raycast(t_ch *c, int x);
void				calc_ray(t_ch *c, int x);
void				dda(t_data *d);

// ---------------------  raycasting/run_util.c  ---------------------//
void				err_exit(const char *str);
void				my_xpm_to_img(t_data *d, int dir, char *wall, int y);
void				draw_floor_ceil(t_ch *c);

// ---------------------  raycasting/run.c  ---------------------//
double				calc_dis(t_ch *c);
void				calc_wall(t_ch *c);
void				map_line(t_ch *c, int x);
void				draw(t_data *d);
int					draw_game(t_data *d);

#endif