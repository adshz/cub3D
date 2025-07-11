/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:55:31 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 15:57:55 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static void	set_frame_image_pixel(t_cub *cub, t_img *image, int x, int y)
{
	if (cub->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, cub->texture_pixels[y][x]);
	else if (y < cub->win_height / 2)
		set_image_pixel(image, x, y, cub->texture_data.hex_ceiling);
	else if (y < cub->win_height - 1)
		set_image_pixel(image, x, y, cub->texture_data.hex_floor);
	return ;
}

static void	render_frame(t_cub *cub)
{
	t_img	image;
	int		x;
	int		y;

	image.img_ptr = NULL;
	init_img(cub, &image, cub->win_width, cub->win_height);
	y = 0;
	while (y < cub->win_height)
	{
		x = 0;
		while (x < cub->win_width)
		{
			set_frame_image_pixel(cub, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, image.img_ptr, 0, 0);
	mlx_destroy_image(cub->mlx_ptr, image.img_ptr);
}

static void	render_raycast(t_cub *cub)
{
	init_texture_pixels(cub);
	init_ray(&cub->ray);
	build_raycasting(&cub->player, cub);
	render_frame(cub);
}

void	render_game(t_cub *cub)
{
	render_raycast(cub);
	if (BONUS)
		render_minimap(cub);
}

int	render_wrapper(t_cub *cub)
{
	cub->player.has_moved += move_player(cub);
	if (cub->player.has_moved == 0)
		return (0);
	render_game(cub);
	return (0);
}
