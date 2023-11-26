/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:06:09 by museker           #+#    #+#             */
/*   Updated: 2023/11/20 21:08:32 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <time.h>
# include <fcntl.h>
# include <unistd.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

#define	FRAME_PER_SEC = 2;
#define screenWidth 2000
#define screenHeight 1200
// #define mapWidth 24
// #define mapHeight 24

typedef struct s_ch 
{
	double		ch_pos[3]; // 0 = x pos | 1 = y pos | 3 = (char)direction
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	clock_t		time;
	clock_t		oldTime;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	double		frameTime;
	int			mapX;
	int			mapY;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	double		moveSpeed;
	double		rotSpeed;
}	t_ch;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*north_wall;
	void	*west_wall;
	void	*south_wall;
	void	*east_wall;
	void	*sky;
	void	*floor;
	void	*kare;
	void	*duvar;
}	t_game;

typedef struct s_data
{
	char	**all_map;
	char	**map;
	char	**redirect;
	char	***r_paths;
	int		file_width;
	int		file_height;
	int		map_width;
	int		map_height;
	int		win_width;
	int		win_height;
	int		map_location;
	int		*f;
	int		*c;
	t_game	g;
	t_ch	*ch;
}	t_data;

// ---------------------------  main.c  ----------------------------//
void	ft_init(t_data *data, char *address);

// ---------------------  parser/check_map.c  ---------------------//
void	ft_error(char *str, int i, int j);
int		ft_strlen_one_zero_map(t_data *data, char **s);
void	ft_check_one_zero_map(t_data *d);
void	ft_check_redirects(t_data *d);
void	ft_checkmap(t_data *data);

// ---------------------  parser/check_map2.c  ---------------------//
void	is_connected_map(t_data *d);
void	check_player(t_data *data);

// ---------------------  parser/chec.c  ---------------------//
void	ft_checkdirect(t_data *data);

// ---------------------  parser/get_map.c -------------------------//
void	print_double_pointer(char **str);
void	print_int_pointer(int *a);
int		map_size(char **s);
void	get_all_map_size(t_data *data, char *address);
void	set_redirects(t_data *data);
void	ft_getmap(t_data *d, int i);
void	get_all_map(t_data *data, char *address);

void	check_value_of_redirect(char ***s);
void	ch_direction(t_data *d);
int		raycasting(t_data *d);

#endif
