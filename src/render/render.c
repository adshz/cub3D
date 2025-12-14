/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:55:31 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 15:57:55 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static void	clear_image(mlx_image_t *img)
{
	ft_memset(img->pixels, 0, img->width * img->height * sizeof(uint32_t));
}

static void	set_frame_pixel(t_cub *cub, int x, int y)
{
	if (cub->texture_pixels[y][x] > 0)
		put_pixel(cub->frame, x, y, cub->texture_pixels[y][x]);
	else if (y < cub->win_height / 2)
		put_pixel(cub->frame, x, y, cub->texture_data.hex_ceiling);
	else if (y < cub->win_height - 1)
		put_pixel(cub->frame, x, y, cub->texture_data.hex_floor);
}

static void	render_frame(t_cub *cub)
{
	int	x;
	int	y;

	clear_image(cub->frame);
	y = 0;
	while (y < cub->win_height)
	{
		x = 0;
		while (x < cub->win_width)
		{
			set_frame_pixel(cub, x, y);
			x++;
		}
		y++;
	}
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

void	render_wrapper(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	cub->player.has_moved += move_player(cub);
	if (cub->player.has_moved == 0)
		return ;
	render_game(cub);
	cub->player.has_moved = 0;
}
