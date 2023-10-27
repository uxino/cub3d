#include "../cub3d.h"

void	is_connected_map(t_data *d)
{
	int	i;
	int	j;

	i = -1;
	while (d->map[++i])
	{
		j = -1;
		while (d->map[i][++j])
		{
			if (d->map[i][j] == '1')
			{
				if ((j -1 >= 0 && (d->map[i][j - 1] == '1'
					|| d->map[i][j - 1] == '0'))
					|| (i - 1 >= 0 && (d->map[i - 1][j] == '1' || d->map[i - 1][j] == '0'))
					|| (j + 1 <= d->map_width + 1 && (d->map[i][j + 1] == '1' || d->map[i][j + 1] == '0'))
					|| (i + 1 <= d->map_height + 1 && (d->map[i + 1][j] == '1' || d->map[i + 1][j] == '0'))
					|| (i-1 == -1 && (d->map[0][j] == '1' || d->map[0][j] == '0'))
					|| (j-1 == -1 && (d->map[i][0] == '1' || d->map[i][0] == '0')))
					continue;
				else
					ft_error("Error: Map is not valid", i, j);
			}
		}
	}
}
