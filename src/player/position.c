/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:36:41 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 16:42:34 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static bool	is_wall_collision(t_cub *cub, double x, double y)
{
	if (cub->map_matrix[(int)y][(int)x] == '0')
		return (false);
	return (true);
}

static bool	is_in_map(t_cub *cub, double x, double y)
{
	if (x < 0.25 || x >= cub->map_data.width - 1.25)
		return (false);
	if (y < 0.25 || y >= cub->map_data.height - 0.25)
		return (false);
	return (true);
}

static bool	is_valid_pos(t_cub *cub, double x, double y)
{
	if (!BONUS && is_in_map(cub, x, y))
		return (true);
	if (BONUS && is_wall_collision(cub, x, y))
		return (true);
	return (false);
}

int	validate_move(t_cub *cub, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (is_valid_pos(cub, new_x, cub->player.pos_y))
	{
		cub->player.pos_x = new_x;
		moved = 1;
	}
	if (is_valid_pos(cub, cub->player.pos_x , new_y))
	{
		cub->player.pos_y = new_y;
		moved = 1;
	}
	return (moved);
}

