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

void	render_minimap(t_cub *cub)
{
	t_minimap	minimap;

	minimap.map = NULL;
	minimap.distance = MINIMAP_VIEW_DIST;
	minimap.size = (2 * minimap.distance) + 1;
	minimap.tile_size = MINIMAP_PIXEL_SIZE / (2 * minimap.distance);
	minimap.offset_x = get_minimap_offset(
			&minimap, cub->map_data.width,
			(int)cub->player.pos_x);
	minimap.offset_y = get_minimap_offset(
			&minimap, cub->map_data.height,
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
