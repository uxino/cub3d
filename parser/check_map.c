/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:33:22 by museker           #+#    #+#             */
/*   Updated: 2023/10/26 19:03:56 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(char *str, int i, int j)
{
	printf("%s i: %d j:%d\n", str, i, j);
	exit(0);
}

int	ft_strlen_one_zero_map(t_data *data, char **s)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (s[++i])
		if (s[i][0] != '\n')
			count++;
	data->map_height = count;
	return (count);
}

void	ft_check_one_zero_map(t_data *d)
{
	int	i;
	int	j;

	i = -1;
	d->map_height = map_size(d->map);
	d->map_width = d->allmap_width;
	while (d->map[++i])
	{
		j = -1;
		while (d->map[i][++j])
			if (d->map[i][j] == '0')
				if ((j - 1 > 0 && d->map[i][j - 1] == '*')
					|| (j - 1 == -1 && d->map[i][0] == '0')
					|| (i - 1 == -1 && d->map[0][j] == '0')
					|| (j + 1 <= d->map_width + 1 && (d->map[i][j + 1] == '*'
					|| !d->map[i][j + 1]))
					|| (i - 1 > 0 && (d->map[i - 1][j] == '*'
					|| !d->map[i - 1][j]))
					|| (i + 1 <= d->map_height + 1 && (d->map[i + 1][j] == '*'
					|| !d->map[i + 1][j])))
					ft_error("Error: Map is not valid", i, j);
	}
}

void	ft_check_directions(t_data *d)
{
	int	i;
	int	count;
	int	count2;

	count2 = 0;
	count = 0;
	i = -1;
	while (d->redirect[++i])
		if (!ft_strchr(d->redirect[i], '\t')
			&& ((ft_strnstr(d->redirect[i], "NO", ft_strlen(d->redirect[i]))
			|| ft_strnstr(d->redirect[i], "SO", ft_strlen(d->redirect[i]))
			|| ft_strnstr(d->redirect[i], "EA", ft_strlen(d->redirect[i]))
			|| ft_strnstr(d->redirect[i], "WE", ft_strlen(d->redirect[i]))
			|| ft_strnstr(d->redirect[i], "C", ft_strlen(d->redirect[i]))
			|| ft_strnstr(d->redirect[i], "F", ft_strlen(d->redirect[i])))))
			count++;
	i = -1;
	while (d->redirect[++i])
	{
		if (d->redirect[i][0] == '\n')
			continue ;
		count2++;
	}
	if (count != count2)
		ft_error("Error: Invalid direction", -1, -1);
}


void	ft_checkmap(t_data *data)
{
	if (ft_strlen_one_zero_map(data, data->redirect) != 6)
		ft_error("Error: Invalid direction", -1, -1);
	ft_check_directions(data);
	ft_check_one_zero_map(data);
	is_connected_map(data);
}
