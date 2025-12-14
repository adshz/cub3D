/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:22:32 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 16:52:01 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static void	handle_key_press(mlx_key_data_t keydata, t_cub *cub)
{
	if (keydata.key == KEY_ESC)
		mlx_close_window(cub->mlx);
	if (keydata.key == KEY_LEFT)
		cub->player.rotate -= 1;
	if (keydata.key == KEY_RIGHT)
		cub->player.rotate += 1;
	if (keydata.key == KEY_W)
		cub->player.move_y = 1;
	if (keydata.key == KEY_D)
		cub->player.move_x = 1;
	if (keydata.key == KEY_S)
		cub->player.move_y = -1;
	if (keydata.key == KEY_A)
		cub->player.move_x = -1;
}

static void	handle_key_release(mlx_key_data_t keydata, t_cub *cub)
{
	if (keydata.key == KEY_W && cub->player.move_y == 1)
		cub->player.move_y = 0;
	if (keydata.key == KEY_D && cub->player.move_x == 1)
		cub->player.move_x = 0;
	if (keydata.key == KEY_S && cub->player.move_y == -1)
		cub->player.move_y = 0;
	if (keydata.key == KEY_A && cub->player.move_x == -1)
		cub->player.move_x = 0;
	if (keydata.key == KEY_LEFT && cub->player.rotate <= 1)
		cub->player.rotate = 0;
	if (keydata.key == KEY_RIGHT && cub->player.rotate >= -1)
		cub->player.rotate = 0;
}

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (keydata.action == MLX_PRESS)
		handle_key_press(keydata, cub);
	else if (keydata.action == MLX_RELEASE)
		handle_key_release(keydata, cub);
}

static void	close_hook(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	mlx_close_window(cub->mlx);
}

void	setup_hooks(t_cub *cub)
{
	mlx_key_hook(cub->mlx, key_hook, cub);
	mlx_close_hook(cub->mlx, close_hook, cub);
	mlx_loop_hook(cub->mlx, render_wrapper, cub);
}
