/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:46:10 by museker           #+#    #+#             */
/*   Updated: 2023/11/27 11:45:25 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_all_map_size(t_data *data, char *address)
{
	int		fd;
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	fd = open(address, O_RDONLY);
	if (fd == -1)
		ft_error("File not found!", -1, -1);
	while (1)
	{
		line = get_next_line(fd);
		if (ft_strlen(line) > j)
			j = ft_strlen(line);
		if (!line)
			break ;
		i++;
		free(line);
	}
	close(fd);
	data->file_width = j;
	data->file_height = i;
}

void	set_redirects(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (data->all_map[++i])
	{
		if (data->all_map[i][0] == '0' || data->all_map[i][0] == '1')
			break ;
		data->redirect[j++] = ft_strdup(data->all_map[i]);
	}
	if (!data->all_map[i])
		ft_error("Map not found!", -1, -1);
	data->redirect[j] = NULL;
	data->map_location = i;
}

void	ft_getmap(t_data *d, int i)
{
	int	j;
	int	k;

	k = 0;
	while (d->all_map[++i])
	{
		j = 0;
		if (ft_strchr(d->all_map[i], '\t'))
			ft_error("Error: Invalid map", i, -1);
		if (!ft_strchr(d->all_map[i], '1') && !ft_strchr(d->all_map[i], '0'))
			break ;
		d->map[k] = malloc(d->file_width + 1);
		while (j < d->file_width - 1)
			ft_getmap2(d, &i, &j, &k);
		j = d->file_width - 1;
		d->map[k][j] = '\0';
		k++;
	}
	d->map[k] = NULL;
}

void	ft_getmap2(t_data *d, int *i, int *j, int *k)
{
	if (ft_strlen(d->all_map[*i]) >= *j && d->all_map[*i][*j]
		&& (d->all_map[*i][*j] == '0'
		|| d->all_map[*i][*j] == '1' || d->all_map[*i][*j] == 'W'
		|| d->all_map[*i][*j] == 'N' || d->all_map[*i][*j] == 'S'
		|| d->all_map[*i][*j] == 'E'))
		d->map[*k][*j] = d->all_map[*i][*j];
	else
	{
		if (!d->all_map[*i][*j] || d->all_map[*i][*j] == '\n')
			while (*j < d->file_width - 1)
				d->map[*k][(*j)++] = '*';
		else if (d->all_map[*i][*j] == ' ')
			d->map[*k][*j] = '*';
		else
			ft_error("Invalid argument in map!", *i, *j);
	}
	(*j)++;
}

void	get_all_map(t_data *data, char *address)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(address, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			data->all_map[i] = NULL;
			break ;
		}
		data->all_map[i] = ft_calloc(data->file_width + 1, sizeof(char));
		ft_memcpy(data->all_map[i], line, data->file_width + 1);
		if (ft_strchr(data->all_map[i], '\t'))
			ft_error("Error: Invalid map", i, -1);
		free(line);
		i++;
	}
	close(fd);
}
