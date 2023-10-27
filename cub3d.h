/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:06:09 by museker           #+#    #+#             */
/*   Updated: 2023/10/26 19:06:10 by museker          ###   ########.fr       */
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

typedef struct s_data
{
	char	**all_map;
	char	**map;
	char	**redirect;
	int		allmap_width;
	int		allmap_height;
	int		map_width;
	int		map_height;
	int		win_width;
	int		win_height;
	int		map_location;
}	t_data;

// ---------------------------  main.c  ----------------------------//
void	ft_init(t_data *data, char *address);

// ---------------------  parser/check_map.c  ---------------------//
void	ft_error(char *str, int i, int j);
int		ft_strlen_one_zero_map(t_data *data, char **s);
void	ft_check_one_zero_map(t_data *d);
void	ft_check_directions(t_data *d);
void	ft_checkmap(t_data *data);

// ---------------------  parser/check_map2.c  ---------------------//
void	is_connected_map(t_data *d);

// ---------------------  parser/get_map.c -------------------------//
void	print_double_pointer(char **str);
int		map_size(char **s);
void	get_all_map_size(t_data *data, char *address);
void	set_directions(t_data *data);
void	ft_getmap(t_data *d, int i);
void	get_all_map(t_data *data, char *address);
#endif
