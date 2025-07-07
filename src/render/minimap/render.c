/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:05:56 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 16:07:28 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static int	get_minimap_offset(t_minimap *minimap, int mapsize, int pos)
{
  if (pos > minimap->distance && mapsize - pos > minimap->distance + 1)
    return (pos - minimap->distance);
  if (pos > minimap->distance && mapsize - pos <= minimap->distance + 1)
    return (mapsize - minimap->size);
  return (0);
}

static bool	is_valid_map_coord(int coord, int size)
{
	if (coord < size)
		return (true);
	return (false);
}

static char	*add_minimap_line(t_cub *cub, t_minimap *minimap, int y)
{
	char	*line;
	int	x;

	line = ft_calloc(minimap->size + 1, sizeof * line);
	if (!line)
		return (NULL);
	x = 0;
	while (x < minimap->size && x < cub->map_data.width)
	{
		if (!is_valid_map_coord(y + minimap->offset_y, cub->map_data.height)
			|| !is_valid_map_coord(x + minimap->offset_x, cub->map_data.width))
			line[x] = '\0';
		else if ((int)cub->player.pos_x == (x + minimap->offset_x)
			&& (int)cub->player.pos_y == (y + minimap->offset_y))
			line[x] = 'P';
		else if (cub->map_matrix[y + minimap->offset_y][x + minimap->offset_x] == '1')
			line[x] = '1';
		else if (cub->map_matrix[y + minimap->offset_y][x + minimap->offset_x] == '0')
			line[x] = '0';
		else
			line[x] = '\0';
		x++;
	}
	return (line);
}

static char	**generate_minimap(t_cub *cub, t_minimap *minimap)
{
	char	**minimap_tmp;
	int	y;

	minimap_tmp = ft_calloc(minimap->size, sizeof * minimap_tmp);
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

void	render_minimap(t_cub *cub)
{
	t_minimap	minimap;

	minimap.map = NULL;
	minimap.img = &cub->minimap;
	minimap.distance = MINIMAP_VIEW_DIST;
	minimap.size =  (2 * minimap.distance) + 1;
	minimap.tile_size = MINIMAP_PIXEL_SIZE / (2 * minimap.distance);
	minimap.offset_x = get_minimap_offset(&minimap, cub->map_data.width, \
									(int)cub->player.pos_x);
	minimap.offset_y = get_minimap_offset(&minimap, cub->map_data.height, \
									(int)cub->player.pos_y);
	minimap.map = generate_minimap(cub, &minimap);
	if (!minimap.map)
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return ;
	}
	if (MINIMAP_DEBUG_MODE)
		debug_display_minimap(&minimap);
	render_minimap_image(cub, &minimap);
	free_matrix((void **)minimap.map);
}
