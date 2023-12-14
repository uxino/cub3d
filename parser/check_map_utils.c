/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:58:58 by mucakmak          #+#    #+#             */
/*   Updated: 2023/11/27 11:12:31 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen_one_zero_map(t_data *data, char **s)
{
	int	i;
	int	count;

	(void)data;
	i = -1;
	count = 0;
	while (s[++i])
		if (s[i][0] != '\n')
			count++;
	return (count);
}

int	ft_check_one_zero_map_2(t_data *d, int i, int j)
{
	if (d->map[i][j] == '0' || d->map[i][j] == 'W' || d->map[i][j] == 'S'
		|| d->map[i][j] == 'N' || d->map[i][j] == 'E')
		return (1);
	return (0);
}

int	c_o_z_m(t_data *d, int i, int j)
{
	if (d->map[i][j] == 'W' || d->map[i][j] == 'S'
		|| d->map[i][j] == 'N' || d->map[i][j] == 'E')
		return (1);
	return (0);
}

int	map_size(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}
