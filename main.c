/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:11:00 by mucakmak          #+#    #+#             */
/*   Updated: 2023/12/12 18:24:35 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(char *str)
{
	if (str)
		printf("%s\n", str);
	exit(0);
}

void	mlx_define(t_data *data)
{
	int	x;
	int	y;

	data->g.mlx = mlx_init();
	data->g.win = mlx_new_window(data->g.mlx, SCREENWIDTH, SCREENHEIGHT,
			"cub3D");
	data->g.sky = mlx_xpm_file_to_image(data->g.mlx, "textures/sky_eagle.xpm",
			&x, &y);
	data->g.floor = mlx_xpm_file_to_image(data->g.mlx,
			"textures/floor_wood.xpm", &x, &y);
	data->g.north_wall = mlx_xpm_file_to_image(data->g.mlx,
			"textures/north_pillar.xpm", &x, &y);
	data->g.east_wall = mlx_xpm_file_to_image(data->g.mlx,
			"textures/east_greystone.xpm", &x, &y);
	data->g.west_wall = mlx_xpm_file_to_image(data->g.mlx,
			"textures/west_mossy.xpm", &x, &y);
	data->g.south_wall = mlx_xpm_file_to_image(data->g.mlx,
			"textures/south_bluestone.xpm", &x, &y);
	init_vec(data->ch, data->ch->ch_pos[2], data->ch->ch_pos[1],
		data->ch->ch_pos[0]);
	init_mlx(data);
	mlx_hook(data->g.win, 2, 1L << 0, key_code, data);
	mlx_loop_hook(data->g.mlx, draw_game, data);
	mlx_hook(data->g.win, 17, 0L, close_game, NULL);
	mlx_loop(data->g.mlx);
}

void	ft_init(t_data *data, char *address)
{
	get_all_map_size(data, address);
	data->all_map = ft_calloc(data->file_height + 1, sizeof(char *));
	data->map = malloc(sizeof(char *) * (data->file_height + 1));
	data->redirect = malloc(sizeof(char *) * (data->file_height + 1));
	get_all_map(data, address);
	set_redirects(data);
	ft_getmap(data, data->map_location - 1);
	ft_checkmap(data);
	ft_checkdirect(data);
}

void	check_file_name(const char *map_name)
{
	int	len;

	len = ft_strlen(map_name) - 4;
	if (ft_strncmp(map_name + len, ".cub", ft_strlen(map_name)))
		ft_error("Map is not .cub format!", -1, -1);
	if (SCREENWIDTH / SCREENHEIGHT != 1 || SCREENWIDTH > 1200
		|| SCREENHEIGHT > 1200)
		ft_error("More window size than excepted!", -1, -1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (0);
	data = malloc(sizeof(t_data));
	data->ch = malloc(sizeof(t_ch));
	if (!data)
		return (0);
	if (argv[1])
		check_file_name(argv[1]);
	ft_init(data, argv[1]);
	mlx_define(data);
	return (0);
}
