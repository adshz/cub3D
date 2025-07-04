/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:59:29 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 18:00:01 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	init_mlx(t_cub *cub)
{
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		clean_exit(cub, err_msg("mlx", "Fail to start mlx", FAILURE));
	cub->win_ptr = mlx_new_window(cub->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "42Cub3D");
	if (!cub->win_ptr)
		clean_exit(cub, err_msg("mlx", "Fail to create a mlx window", FAILURE));
	if (BONUS)
		mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, cub->win_width / 2,
			cub->win_height / 2);
	return ;
}
