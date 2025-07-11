/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:45:37 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 16:50:12 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static int	rotate_calculation(t_cub *cub, double rotspeed)
{
	t_player	*player;
	double		tmp_x;

	player = &cub->player;
	tmp_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rotspeed)
		- player->dir_y * sin(rotspeed);
	player->dir_y = tmp_x * sin(rotspeed) + player->dir_y * cos(rotspeed);
	tmp_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rotspeed)
		- player->plane_y * sin(rotspeed);
	player->plane_y = tmp_x * sin(rotspeed) + player->plane_y * cos(rotspeed);
	return (1);
}

int	move_around(t_cub *cub, double rotdir)
{
	int		moved;
	double	rotspeed;

	moved = 0;
	rotspeed = ROTSPEED * rotdir;
	moved += rotate_calculation(cub, rotspeed);
	return (moved);
}
