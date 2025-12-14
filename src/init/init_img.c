/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:42:58 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 15:32:08 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

mlx_texture_t	*load_texture(t_cub *cub, char *filepath)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(filepath);
	if (!texture)
		clean_exit(cub, err_msg(filepath, "Failed to load texture", FAILURE));
	return (texture);
}
