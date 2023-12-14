/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucakmak <mucakmak@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:54:52 by museker           #+#    #+#             */
/*   Updated: 2023/12/14 20:14:05 by mucakmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_check_redirect3(t_data *data, int i, char c)
{
	char	**tmp;
	int		j;

	j = -1;
	if (data->redirect[i][0] && data->redirect[i][0] == c)
	{
		tmp = ft_split(data->redirect[i] + 2, ',');
		while (tmp[++j])
			ft_check_value(tmp[j]);
	}
}

void	ft_checkdirect(t_data *data)
{
	int		i;

	i = -1;
	split_direct(data);
	check_value_of_redirect(data->r_paths);
	split_color_code(data);
	while (data->redirect[++i])
	{
		ft_check_redirect3(data, i, 'F');
		ft_check_redirect3(data, i, 'C');
	}
}
