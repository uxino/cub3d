/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:54:52 by museker           #+#    #+#             */
/*   Updated: 2023/12/14 20:19:39 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	split_c(t_data *d, int i)
{
	char	*tmp;
	char	**tmptwo;
	int		j;
	int		e;

	j = -1;
	e = -1;
	tmp = NULL;
	if (ft_strchr(d->r_paths[i][0], 'C'))
	{
		tmp = two_pointer_to_one_pointer(d->r_paths[i]);
		tmptwo = ft_split(tmp, ',');
		free(tmp);
		while (tmptwo[++j])
		{
			d->c[++e] = ft_atoi(tmptwo[j]);
			free(tmptwo[j]);
		}
		free(tmptwo);
		if (j != 3)
			ft_error("C wrong!!", -1, -1);
		d->c[++e] = -31;
		d->c[++e] = '\0';
	}
}

void	ft_check_value(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			while (s[i] && s[i] >= '0' && s[i] <= '9')
				i++;
			while (s[i] && !(s[i] >= '0' && s[i] <= '9'))
				i++;
			if (s[i])
				ft_error("values are not valid!!", -1, -1);
		}
	}
	i = -1;
	while (s[++i])
	{
		if (!(s[i] >= '0' && s[i] <= '9') && s[i] != ' ' && s[i] != '\n')
			ft_error("values are not valid!!", -1, -1);
	}
}

void	split_f(t_data *d, int i)
{
	char	*tmp;
	char	**tmptwo;
	int		j;
	int		e;

	j = -1;
	e = -1;
	if (ft_strchr(d->r_paths[i][0], 'F'))
	{
		tmp = two_pointer_to_one_pointer(d->r_paths[i]);
		tmptwo = ft_split(tmp, ',');
		free(tmp);
		while (tmptwo[++j])
		{
			d->f[++e] = ft_atoi(tmptwo[j]);
			free(tmptwo[j]);
		}
		free(tmptwo);
		if (j != 3)
			ft_error("F wrong!!", -1, -1);
		d->f[++e] = -31;
		d->f[++e] = '\0';
	}
}

void	split_color_code(t_data *d)
{
	int		i;

	i = 0;
	d->c = malloc(sizeof(int) * 5);
	d->f = malloc(sizeof(int) * 5);
	while (d->r_paths[++i])
	{
		if (ft_strchr(d->r_paths[i][0], 'F'))
			split_f(d, i);
		if (ft_strchr(d->r_paths[i][0], 'C'))
			split_c(d, i);
	}
	set_color(&d->ch->fl, d->f);
	set_color(&d->ch->ce, d->c);
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
		{
			if (!ft_strchr(s[j][0], 'C') && !ft_strchr(s[j][0], 'F'))
				if (!ft_strncmp(s[j][1], p, ft_strlen(s[j][1])))
					ft_error("redirect is not valid!!", -1, -1);
		}
	}
}
