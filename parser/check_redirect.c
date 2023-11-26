/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: museker <museker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:54:52 by museker           #+#    #+#             */
/*   Updated: 2023/11/02 16:44:10 by museker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	two_pointer_free(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

int	two_pointer_size(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

void	split_direct(t_data *d)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	d->r_paths = malloc(sizeof(char **) * 7);
	while (d->redirect[++i])
	{
		if (d->redirect[i][0] == '\n')
			continue ;
		d->r_paths[++j] = ft_split(d->redirect[i], ' ');
		if (!d->r_paths[j] || !d->r_paths[j][0] || !d->r_paths[j][1]
			|| d->r_paths[j][1][0] == '\n')
			ft_error("Invalid redirect paths!", -1, -1);
	}
	d->r_paths[++j] = NULL;
}

void	split_color_code(t_data *d)
{
	int		i;
	int		j;
	int		e;
	int		size;

	i = -1;
	d->c = malloc(sizeof(int) * 100);
	d->f = malloc(sizeof(int) * 100);
	while (d->r_paths[++i])
	{
		if (ft_strchr(d->r_paths[i][0], 'C'))
		{
			size = 6;
			j = 0;
			e = -1;
			while (--size > 0 && ++j)
			{
				if (ft_strchr(d->r_paths[i][j], ','))
					continue ;
				d->c[++e] = ft_atoi(d->r_paths[i][j]);
			}
			d->c[++e] = '\0';
		}
		else if (ft_strchr(d->r_paths[i][0], 'F'))
		{
			size = 6;
			j = 0;
			e = -1;
			while (--size > 0 && ++j)
			{
				if (ft_strchr(d->r_paths[i][j], ','))
					continue ;
				d->f[++e] = ft_atoi(d->r_paths[i][j]);
			}
			d->f[++e] = '\0';
		}
	}
}

void	check_value_of_redirect(char ***s)
{
	int		i;
	char	*p;
	int		j;

	i = -1;
	while (s[++i])
	{
		p = s[i][1];
		j = i;
		while (s[++j])
			if (!ft_strncmp(s[j][1], p, ft_strlen(s[j][1])))
				ft_error("Error: redirect is not valid elma :)", -1, -1);
	}
}

void	ft_checkdirect(t_data *data)
{
	split_direct(data);
	check_value_of_redirect(data->r_paths);
	split_color_code(data);
}


		// if (d->r_paths[i][1][0])
		// else if (d->r_paths[i][0] && ft_strnstr(d->r_paths[i][0],
		// 	"C", ft_strlen(d->redirect[i])))
		// {
		// 	j = -1;
		// 	s = ft_split(d->r_paths[i][1], ',');
		// 	while (++j < 3)
		// 		d->c[j] = ft_atoi(s[j]);
		// }
		// else if (d->r_paths[i][0] && ft_strnstr(d->r_paths[i][0], "F", ft_strlen(d->redirect[i])))
		// {
		// 	j = -1;
		// 	s = ft_split(d->r_paths[i][1], ',');
		// 	while (++j < 3)
		// 		d->f[j] = ft_atoi(s[j]);
		// }


			// 	printf("d->f[e] = (%s)\n", d->r_paths[i][j]);

			// if (ft_strchr(d->r_paths[i][0], 'C'))
			// {
			// 	e = -1;
			// 	if (ft_strchr(d->r_paths[i][j], ','))
			// 		continue ;  						// en son
				
			// 	d->c[++e] = ft_atoi(d->r_paths[i][j]);
			// }
			// if (ft_strchr(d->r_paths[i][0], 'F'))
			// {
			// 	e = -1;
			// 	if (ft_strchr(d->r_paths[i][j], ','))
			// 		continue ;
			// 	d->f[++e] = ft_atoi(d->r_paths[i][j]);
			// }