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

int	get_minimap_offset(t_minimap *minimap, int mapsize, int pos)
{
	if (pos > minimap->distance && mapsize - pos > minimap->distance + 1)
		return (pos - minimap->distance);
	if (pos > minimap->distance && mapsize - pos <= minimap->distance + 1)
		return (mapsize - minimap->size);
	return (0);
}

bool	is_valid_map_coord(int coord, int size)
{
	if (coord < size)
		return (true);
	return (false);
}

char	get_minimap_char(t_cub *cub, int map_x, int map_y)
{
	if (!is_valid_map_coord(map_y, cub->map_data.height)
		|| !is_valid_map_coord(map_x, cub->map_data.width))
		return ('\0');
	if ((int)cub->player.pos_x == map_x
		&& (int)cub->player.pos_y == map_y)
		return ('P');
	if (cub->map_matrix[map_y][map_x] == '1')
		return ('1');
	if (cub->map_matrix[map_y][map_x] == '0')
		return ('0');
	return ('\0');
}
