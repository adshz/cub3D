/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:35:03 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 16:36:05 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static int	move_forward(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x + cub->player.dir_x * MOVESPEED;
	new_y = cub->player.pos_y + cub->player.dir_y * MOVESPEED;
	return (validate_move(cub, new_x ,new_y));
}

static int	move_backward(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x - cub->player.dir_y * MOVESPEED;
	new_y = cub->player.pos_y - cub->player.dir_x * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

static int	move_right(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x - cub->player.dir_y * MOVESPEED;
	new_y = cub->player.pos_y + cub->player.dir_x * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

static int	move_left(t_cub *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x + cub->player.dir_y * MOVESPEED;
	new_y = cub->player.pos_y - cub->player.dir_x * MOVESPEED;
	return (validate_move(cub, new_x, new_y));
}

int	move_player(t_cub *cub)
{
	int	moved;

	moved = 0;
	if (cub->player.move_y == 1)
		moved += move_forward(cub);
	if (cub->player.move_y == -1)
		moved += move_backward(cub);
	if (cub->player.move_x == -1)
		moved += move_left(cub);
	if (cub->player.move_x == 1)
		moved += move_right(cub);
	if (cub->player.rotate != 0)
		moved += move_around(cub, cub->player.rotate);
	return (moved);
}
