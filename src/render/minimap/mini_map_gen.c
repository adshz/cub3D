/* ************************************************************************** */
/*                                                                            */
/*                                                    :::      ::::::::       */
/*   minimap_utils.c                                 :+:      :+:    :+:      */
/*                                                  +:+ +:+         +:+       */
/*   By: alissa <aalissa@student.42london.com>     +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:00:00 by alissa            #+#    #+#             */
/*   Updated: 2025/07/15 20:00:00 by alissa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*add_minimap_line(t_cub *cub, t_minimap *minimap, int y)
{
	char	*line;
	int		x;
	int		map_y;
	int		map_x;

	line = ft_calloc(minimap->size + 1, sizeof(*line));
	if (!line)
		return (NULL);
	x = 0;
	map_y = y + minimap->offset_y;
	while (x < minimap->size && x < cub->map_data.width)
	{
		map_x = x + minimap->offset_x;
		line[x] = get_minimap_char(cub, map_x, map_y);
		x++;
	}
	return (line);
}

char	**generate_minimap(t_cub *cub, t_minimap *minimap)
{
	char	**minimap_tmp;
	int		y;

	minimap_tmp = ft_calloc(minimap->size + 1, sizeof(*minimap_tmp));
	if (!minimap_tmp)
		return (NULL);
	y = 0;
	while (y < minimap->size && y < cub->map_data.height)
	{
		minimap_tmp[y] = add_minimap_line(cub, minimap, y);
		if (!minimap_tmp[y])
		{
			free_matrix((void **)minimap_tmp);
			return (NULL);
		}
		y++;
	}
	return (minimap_tmp);
}
