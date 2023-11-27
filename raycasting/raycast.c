/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 07:51:35 by museker           #+#    #+#             */
/*   Updated: 2023/11/27 11:09:58 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_raycast(t_ch *c, int x)
{
	c->cam_x = 2 * x / (double)SCREENWIDTH - 1;
	c->raydir_x = c->dir_x + c->pln_x * c->cam_x;
	c->raydir_y = c->dir_y + c->pln_y * c->cam_x;
	c->map_x = (int)c->pos_x;
	c->map_y = (int)c->pos_y;
	c->deltadist_x = fabs(1 / c->raydir_x);
	c->deltadist_y = fabs(1 / c->raydir_y);
	c->hit = 0;
}

void	calc_ray(t_ch *c, int x)
{
	init_raycast(c, x);
	if (c->raydir_x < 0)
	{
		c->step_x = -1;
		c->sidedist_x = (c->pos_x - c->map_x) * c->deltadist_x;
	}
	else
	{
		c->step_x = 1;
		c->sidedist_x = (c->map_x + 1.0 - c->pos_x) * c->deltadist_x;
	}
	if (c->raydir_y < 0)
	{
		c->step_y = -1;
		c->sidedist_y = (c->pos_y - c->map_y) * c->deltadist_y;
	}
	else
	{
		c->step_y = 1;
		c->sidedist_y = (c->map_y + 1.0 - c->pos_y) * c->deltadist_y;
	}
}

void	dda(t_data *d)
{
	while (d->ch->hit == 0)
	{
		if (d->ch->sidedist_x < d->ch->sidedist_y)
		{
			d->ch->sidedist_x += d->ch->deltadist_x;
			d->ch->map_x += d->ch->step_x;
			if (d->ch->step_x == 1)
				d->ch->side1 = 0;
			else
				d->ch->side1 = 1;
		}
		else
		{
			d->ch->sidedist_y += d->ch->deltadist_y;
			d->ch->map_y += d->ch->step_y;
			if (d->ch->step_y == 1)
				d->ch->side1 = 2;
			else
				d->ch->side1 = 3;
		}
		if (d->map[d->ch->map_y][d->ch->map_x] == '1')
			d->ch->hit = 1;
	}
}
