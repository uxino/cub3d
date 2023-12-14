/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:24:01 by mucakmak          #+#    #+#             */
/*   Updated: 2023/12/11 01:43:14 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate(t_ch *v, int opt)
{
	double	dir_x;
	double	pln_x;
	double	rot;

	dir_x = v->dir_x;
	pln_x = v->pln_x;
	rot = (double)ROT_SPEED / 10 * opt;
	v->dir_x = dir_x * cos(rot) - v->dir_y * sin(rot);
	v->dir_y = dir_x * sin(rot) + v->dir_y * cos(rot);
	v->pln_x = pln_x * cos(rot) - v->pln_y * sin(rot);
	v->pln_y = pln_x * sin(rot) + v->pln_y * cos(rot);
}

void	move_ws(t_data *d, double opt)
{
	double	des_x;
	double	des_y;

	des_x = d->ch->pos_x + d->ch->dir_x * (double)MOVE_SPEED / 10 * opt;
	des_y = d->ch->pos_y + d->ch->dir_y * (double)MOVE_SPEED / 10 * opt;
	if (d->map[(int)d->ch->pos_y][(int)des_x] == '0')
		d->ch->pos_x = des_x;
	if (d->map[(int)des_y][(int)d->ch->pos_x] == '0')
		d->ch->pos_y = des_y;
}

void	move_ad(t_data *d, double opt)
{
	double	des_x;
	double	des_y;

	des_x = d->ch->pos_x + d->ch->pln_x * (double)MOVE_SPEED / 10 * opt;
	des_y = d->ch->pos_y + d->ch->pln_y * (double)MOVE_SPEED / 10 * opt;
	if (d->map[(int)d->ch->pos_y][(int)des_x] == '0')
		d->ch->pos_x = des_x;
	if (d->map[(int)des_y][(int)d->ch->pos_x] == '0')
		d->ch->pos_y = des_y;
}

int	close_win(t_data *d)
{
	mlx_clear_window(d->g.mlx, d->g.win);
	mlx_destroy_window(d->g.mlx, d->g.win);
	exit(0);
}

int	key_code(int keycode, t_data *d)
{
	if (keycode == 13)
		move_ws(d, 1);
	if (keycode == 1)
		move_ws(d, -1);
	if (keycode == 0)
		move_ad(d, -1);
	if (keycode == 2)
		move_ad(d, 1);
	if (keycode == 124)
		rotate(d->ch, 1);
	if (keycode == 123)
		rotate(d->ch, -1);
	if (keycode == 53)
		close_win(d);
	return (0);
}
