/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 07:50:26 by museker           #+#    #+#             */
/*   Updated: 2023/12/11 16:58:06 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	calc_dis(t_ch *c)
{
	if (c->side1 == 0 || c->side1 == 1)
	{
		c->wall_dist = (c->map_x - c->pos_x + \
			(1 - c->step_x) / 2) / c->raydir_x;
		if (c->wall_dist <= 0.000001)
			c->wall_dist = 0.00001;
		return (c->pos_y + c->wall_dist * c->raydir_y);
	}
	c->wall_dist = (c->map_y - c->pos_y + \
		(1 - c->step_y) / 2) / c->raydir_y;
	if (c->wall_dist <= 0.000001)
		c->wall_dist = 0.00001;
	return (c->pos_x + c->wall_dist * c->raydir_x);
}

void	calc_wall(t_ch *c)
{
	double	wall_x;

	wall_x = calc_dis(c);
	wall_x -= floor(wall_x);
	c->line_h = (SCREENHEIGHT / c->wall_dist);
	c->side2 = c->side1;
	c->tex_x = (int)(wall_x * (double)PIX);
	if (((c->side1 == 0) || (c->side1 == 1)) && c->raydir_x < 0)
		c->tex_x = PIX - c->tex_x - 1;
	if (((c->side1 == 2) || (c->side1 == 3)) && c->raydir_y > 0)
		c->tex_x = PIX - c->tex_x - 1;
	c->draw_start = -c->line_h / 2 + SCREENHEIGHT / 2;
	if (c->draw_start < 0)
		c->draw_start = 0;
	c->draw_end = c->line_h / 2 + SCREENHEIGHT / 2;
	if (c->draw_end >= SCREENHEIGHT)
		c->draw_end = SCREENHEIGHT - 1;
}

void	map_line(t_ch *c, int x)
{
	double	step;
	double	tex_pos;
	int		i;
	int		tex_y;
	int		color;

	step = 1.0 * PIX / c->line_h;
	tex_pos = (c->draw_start - SCREENHEIGHT / 2 + c->line_h / 2) * step;
	i = c->draw_start;
	while (i <= c->draw_end)
	{
		tex_y = (int)tex_pos & (PIX - 1);
		tex_pos += step;
		color = c->texture[c->side2][PIX * tex_y + c->tex_x];
		c->tmp[i][x] = color;
		i++;
	}
}

void	draw(t_data *d)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREENHEIGHT)
	{
		x = -1;
		while (++x < SCREENWIDTH)
			d->ch->data[y * SCREENWIDTH + x] = d->ch->tmp[y][x];
	}
	mlx_put_image_to_window(d->g.mlx, \
		d->g.win, d->ch->img_ptr, 0, 0);
}

int	draw_game(t_data *d)
{
	int			x;

	x = -1;
	draw_floor_ceil(d->ch);
	while (++x < SCREENHEIGHT)
	{
		calc_ray(d->ch, x);
		dda(d);
		calc_wall(d->ch);
		map_line(d->ch, x);
	}
	draw(d);
	return (0);
}
