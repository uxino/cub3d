/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 07:50:57 by mucakmak          #+#    #+#             */
/*   Updated: 2023/11/27 11:48:14 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_cub3d(t_ch *c)
{
	c->fl = -1;
	c->ce = -1;
	c->h = 0;
	c->w = 0;
}

void	init_vec(t_ch *v, char c, int x, int y)
{
	v->pos_x = (double)x + 0.5;
	v->pos_y = (double)y + 0.5;
	v->dir_x = 1;
	v->dir_y = 1;
	v->pln_x = 0.66;
	v->pln_y = 0.66;
	if (c == 'N' || c == 'S')
	{
		v->dir_x = 0;
		v->pln_y = 0;
		if (c == 'N')
			v->dir_y *= -1;
		else
			v->pln_x *= -1;
	}
	if (c == 'E' || c == 'W')
	{
		v->dir_y = 0;
		v->pln_x = 0;
		if (c == 'W')
		{
			v->dir_x *= -1;
			v->pln_y *= -1;
		}
	}
}

void	init_texture(t_data *d)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		d->ch->texture[i] = malloc(sizeof(int) * PIX * PIX);
		if (d->ch->texture[i] == NULL)
			ft_error("Malloc!!", -1, -1);
		ft_bzero(d->ch->texture[i], sizeof(int) * PIX * PIX);
	}
	my_xpm_to_img(d, 0,
		ft_strtrim(d->r_paths[get_value_redirect(d, "WE")][1], "\n"), -1);
	my_xpm_to_img(d, 1,
		ft_strtrim(d->r_paths[get_value_redirect(d, "EA")][1], "\n"), -1);
	my_xpm_to_img(d, 2,
		ft_strtrim(d->r_paths[get_value_redirect(d, "NO")][1], "\n"), -1);
	my_xpm_to_img(d, 3,
		ft_strtrim(d->r_paths[get_value_redirect(d, "SO")][1], "\n"), -1);
	d->ch->img_ptr = mlx_new_image(d->g.mlx, SCREENWIDTH, SCREENHEIGHT);
	d->ch->data = (unsigned int *)mlx_get_data_addr(d->ch->img_ptr, \
		&d->ch->bpp, &d->ch->size_l, &d->ch->endian);
}

void	init_tmp(t_ch *m)
{
	int		i;

	m->tmp = malloc(sizeof(int *) * SCREENHEIGHT);
	if (m->tmp == NULL)
		ft_error("Malloc!!", -1, -1);
	i = -1;
	while (++i < SCREENHEIGHT)
	{
		m->tmp[i] = malloc(sizeof(int) * SCREENWIDTH);
		if (m->tmp[i] == NULL)
			ft_error("Malloc!!", -1, -1);
		ft_bzero(m->tmp[i], sizeof(int) * SCREENWIDTH);
	}
}

void	init_mlx(t_data *d)
{
	init_tmp(d->ch);
	init_texture(d);
}
