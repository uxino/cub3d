/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:23:33 by mucakmak          #+#    #+#             */
/*   Updated: 2023/12/14 20:14:45 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	calc_color(int color, int rgb)
{
	if (rgb < 0 || rgb > 255)
		return (-1);
	color <<= 8;
	return (color |= rgb);
}

void	set_color(int *texture, int *c_or_f)
{
	int		color;
	int		i;

	i = -1;
	color = 0;
	while (c_or_f[++i] != -31)
	{
		color = calc_color(color, c_or_f[i]);
		if (color < 0)
			break ;
	}
	if (color < 0 || i != 3)
		ft_error("Invalid color.", -1, -1);
	*texture = color;
}
