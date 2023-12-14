/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 07:50:45 by mucakmak          #+#    #+#             */
/*   Updated: 2023/12/11 00:47:51 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error2(int x, int y)
{
	if ((x > 15 || y > 15))
		ft_error("Xpm file must be 16x16.", -1, -1);
}

void	my_xpm_to_img(t_data *d, int dir, char *wall, int y)
{
	t_ch	img;
	int		x;
	int		w;
	int		h;

	img.img_ptr = mlx_xpm_file_to_image(d->g.mlx, wall, &w, &h);
	if (!img.img_ptr)
		ft_error("Invalid texture!", -1, -1);
	img.data = (unsigned int *)mlx_get_data_addr(img.img_ptr, \
		&img.bpp, &img.size_l, &img.endian);
	while (++y < h)
	{
		x = -1;
		while (++x < w)
		{
			ft_error2(x, y);
			d->ch->texture[dir][w * y + x] = img.data[w * y + x];
		}
	}
	if (y < 16)
		ft_error("Xpm file must be 16x16.", -1, -1);
	mlx_destroy_image(d->g.mlx, img.img_ptr);
	free(wall);
}

void	draw_floor_ceil(t_ch *c)
{
	int	x;
	int	y;

	x = -1;
	while (++x < SCREENWIDTH)
	{
		y = -1;
		while (++y < SCREENHEIGHT / 2)
		{
			c->tmp[y][x] = c->ce;
			c->tmp[SCREENHEIGHT - y - 1][x] = c->fl;
		}
	}
}
