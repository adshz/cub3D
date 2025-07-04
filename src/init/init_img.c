/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:42:58 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 15:32:08 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	init_img(t_cub *cub, t_img *img, int width, int height)
{
	init_mlx_img(img);
	img->img_ptr = mlx_new_image(cub->mlx_ptr, width, height);
	if (!img->img_ptr)
		clean_exit(cub, err_msg("mlx", "Minilibx image creation failure", 1));
	img->img_initial_data_addr = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, \
												&img->size_line, &img->endian);
	return ;
}

void	init_texture_img(t_cub *cub, t_img *image, char *filepath)
{
	init_mlx_img(image);
	image->img_ptr = mlx_xpm_file_to_image(cub->mlx_ptr, filepath, \
									&cub->texture_data.size, \
										&cub->texture_data.size);
	if (image->img_ptr == NULL)
		clean_exit(cub, err_msg("mlx", "Failed to create mlx image", 1));
	image->img_initial_data_addr = (int *)mlx_get_data_addr(image->img_ptr, \
														&image->bpp, \
										&image->size_line, &image->endian);
	return ;
}

void	init_mlx_img(t_img *mlx_img)
{
	mlx_img->img_ptr = NULL;
	mlx_img->img_initial_data_addr = NULL;
	mlx_img->bpp = 0;
	mlx_img->size_line = 0;
	mlx_img->endian = 0;
	return ;
}
