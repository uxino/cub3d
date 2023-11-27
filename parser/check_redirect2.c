/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:26:20 by mucakmak          #+#    #+#             */
/*   Updated: 2023/11/27 11:14:34 by mucakmak         ###   ########.fr       */
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

int	two_pointer_character_size(char **s)
{
	int	sum;
	int	i;
	int	j;

	i = 0;
	sum = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
			j++;
		sum += j;
		i++;
	}
	return (sum + i);
}

char	*two_pointer_to_one_pointer(char **str)
{
	char	*s;
	int		i;
	int		j;
	int		nbr;

	i = 0;
	nbr = -1;
	s = malloc(two_pointer_character_size(str) + 2);
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			s[++nbr] = str[i][j];
	}
	s[nbr] = '\0';
	return (s);
}

void	split_direct(t_data *d)
{
	int	i;
	int	j;

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
