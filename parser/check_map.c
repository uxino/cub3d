/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:33:22 by museker           #+#    #+#             */
/*   Updated: 2023/11/02 10:03:00 by museker          ###   ########.fr       */
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

void	ft_check_one_zero_map(t_data *d)
{
	int	i;
	int	j;

	i = -1;
	d->map_height = map_size(d->map);
	if (d->map_height < 3)
		ft_error("Invalid map!", -1, -1);
	d->map_width = d->file_width;
	while (d->map[++i])
	{
		j = -1;
		while (d->map[i][++j])
			if (ft_check_one_zero_map_2(d, i, j))
				if ((j - 1 > 0 && d->map[i][j - 1] == '*')
					|| (j - 1 == -1 && ft_check_one_zero_map_2(d, i, 0))
					|| (i - 1 == -1 && ft_check_one_zero_map_2(d, 0, j))
					|| (j + 1 <= d->map_width && (!d->map[i][j + 1]
					|| d->map[i][j + 1] == '*'))
					|| (i - 1 > 0 && (!d->map[i - 1][j]
					|| d->map[i - 1][j] == '*'))
					|| (i + 1 <= d->map_height && (!d->map[i + 1]
					|| d->map[i + 1][j] == '*')))
					ft_error("Error: Map is not valid", i, j);
	}
}

int	ft_check_redirects2(t_data *d, int i)
{
	if (ft_strnstr(d->redirect[i], "NO ", ft_strlen(d->redirect[i]))
		|| ft_strnstr(d->redirect[i], "SO ", ft_strlen(d->redirect[i]))
		|| ft_strnstr(d->redirect[i], "EA ", ft_strlen(d->redirect[i]))
		|| ft_strnstr(d->redirect[i], "WE ", ft_strlen(d->redirect[i]))
		|| ft_strnstr(d->redirect[i], "C ", ft_strlen(d->redirect[i]))
		|| ft_strnstr(d->redirect[i], "F ", ft_strlen(d->redirect[i])))
		return (1);
	return (0);
}

void	ft_check_redirects(t_data *d)
{
	int	i;
	int	count;
	int	count2;

	count2 = 0;
	count = 0;
	i = -1;
	while (d->redirect[++i])
		if (!ft_strchr(d->redirect[i], '\t')
			&& (ft_check_redirects2(d, i)))
			count++;
	i = -1;
	while (d->redirect[++i])
	{
		if (d->redirect[i][0] == '\n')
			continue ;
		else if (!ft_strchr(d->redirect[i], ' '))
			ft_error("Error: Invalid redirect", i, 0);
		count2++;
	}
	if (count != count2)
		ft_error("Error: Invalid redirect", -1, -1);
}

void	ft_checkmap(t_data *data)
{
	if (ft_strlen_one_zero_map(data, data->redirect) != 6)
		ft_error("Error: Invalid redirect", -1, -1);
	ft_check_redirects(data);
	ft_check_one_zero_map(data);
	is_connected_map(data);
	check_player(data);
}
