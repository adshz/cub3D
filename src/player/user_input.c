/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:22:32 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 16:52:01 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static int	key_press_handler(int key, t_cub *cub)
{
	if (key == XK_Escape)
		quit_game(cub);
	if (key == XK_Left)
		cub->player.rotate -= 1;
	if (key == XK_Right)
		cub->player.rotate += 1;
	if (key == XK_w)
		cub->player.move_y = 1;
	if (key == XK_d)
		cub->player.move_x = 1;
	if (key == XK_s)
		cub->player.move_y = -1;
	if (key == XK_a)
		cub->player.move_x = -1;
	return (0);
}

static int	key_release_handler(int key, t_cub *cub)
{
	if (key == XK_Escape)
		quit_game(cub);
	if (key == XK_w && cub->player.move_y == 1)
		cub->player.move_y = 0;
	if (key == XK_d && cub->player.move_x == 1)
		cub->player.move_x -= 1;
	if (key == XK_s && cub->player.move_y == -1)
		cub->player.move_y = 0;
	if (key == XK_a && cub->player.move_x == -1)
		cub->player.move_x += 1;
	if (key == XK_Left && cub->player.rotate <= 1)
		cub->player.rotate = 0;
	if (key == XK_Right && cub->player.rotate >= -1)
		cub->player.rotate = 0;
	return (0);
}

static void	wrap_mouse_position(t_cub *cub, int x, int y)
{
	if (x > cub->win_width - DIST_EDGE_MOUSE_WRAP)
	{
		x = DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, x, y);
	}
	if (x < DIST_EDGE_MOUSE_WRAP)
	{
		x = cub->win_width - DIST_EDGE_MOUSE_WRAP;
		mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, x, y);
	}
}

static int	mouse_motion_handler(int x, int y, t_cub *cub)
{
	static int	old_x = WIN_WIDTH / 2;

	wrap_mouse_position(cub, x, y);
	if (old_x == x)
		return (0);
	else if (old_x > x)
		cub->player.has_moved += move_around(cub, -1);
	else if (old_x < x)
		cub->player.has_moved += move_around(cub, 1);
	old_x = x;
	return (0);
}

void	event_listening(t_cub *cub)
{
	mlx_hook(cub->win_ptr, ClientMessage, NoEventMask, quit_game, cub);
	mlx_hook(cub->win_ptr, KeyPress, KeyPressMask, key_press_handler, cub);
	mlx_hook(
		cub->win_ptr,
		KeyRelease,
		KeyReleaseMask,
		key_release_handler,
		cub);
	if (BONUS)
		mlx_hook(cub->win_ptr, MotionNotify, PointerMotionMask,
			mouse_motion_handler, cub);
}
