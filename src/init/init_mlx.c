/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                        :+:      :+:    :+:   */
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
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "42Cub3D", false);
	if (!cub->mlx)
		clean_exit(cub, err_msg("mlx", "Failed to initialize MLX42", FAILURE));
	cub->frame = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->frame)
		clean_exit(cub, err_msg("mlx", "Failed to create frame image", FAILURE));
	if (mlx_image_to_window(cub->mlx, cub->frame, 0, 0) < 0)
		clean_exit(cub, err_msg("mlx", "Failed to put image to window", FAILURE));
}
