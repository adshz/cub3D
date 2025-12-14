/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:09:27 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 16:20:14 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static uint32_t	to_rgba(int color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

static void	set_minimap_tile_pixels(
			mlx_image_t *img, t_minimap *minimap, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < minimap->tile_size)
	{
		j = 0;
		while (j < minimap->tile_size)
		{
			put_pixel(img, x + j, i + y, to_rgba(color));
			j++;
		}
		i++;
	}
}

static void	draw_minimap_tile(mlx_image_t *img, t_minimap *minimap, int x, int y)
{
	if (minimap->map[y][x] == 'P')
		set_minimap_tile_pixels(img, minimap, x * minimap->tile_size,
			y * minimap->tile_size, MINIMAP_COLOR_PLAYER);
	else if (minimap->map[y][x] == '1')
		set_minimap_tile_pixels(img, minimap, x * minimap->tile_size,
			y * minimap->tile_size, MINIMAP_COLOR_WALL);
	else if (minimap->map[y][x] == '0')
		set_minimap_tile_pixels(img, minimap, x * minimap->tile_size,
			y * minimap->tile_size, MINIMAP_COLOR_FLOOR);
	else if (minimap->map[y][x] == ' ')
		set_minimap_tile_pixels(img, minimap, x * minimap->tile_size,
			y * minimap->tile_size, MINIMAP_COLOR_SPACE);
}

static void	set_minimap_border(mlx_image_t *img, t_minimap *minimap, int color)
{
	int	size;
	int	x;
	int	y;

	size = MINIMAP_PIXEL_SIZE + minimap->tile_size;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x <= size)
		{
			if (x < 5 || x > size - 5 || y < 5 || y > size - 5)
				put_pixel(img, x, y, to_rgba(color));
			x++;
		}
		y++;
	}
}

static void	draw_minimap(mlx_image_t *img, t_minimap *minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < minimap->size)
	{
		x = 0;
		while (x < minimap->size)
		{
			if (!minimap->map[y]
				|| !minimap->map[y][x]
				|| minimap->map[y][x] == '\0')
				break ;
			draw_minimap_tile(img, minimap, x, y);
			x++;
		}
		y++;
	}
	set_minimap_border(img, minimap, MINIMAP_COLOR_SPACE);
}

void	render_minimap_image(t_cub *cub, t_minimap *minimap)
{
	int			img_size;
	int			pos_x;
	int			pos_y;

	img_size = MINIMAP_PIXEL_SIZE + minimap->tile_size;
	if (cub->minimap_img)
		mlx_delete_image(cub->mlx, cub->minimap_img);
	cub->minimap_img = mlx_new_image(cub->mlx, img_size, img_size);
	if (!cub->minimap_img)
		return ;
	draw_minimap(cub->minimap_img, minimap);
	pos_x = minimap->tile_size;
	pos_y = cub->win_height - (MINIMAP_PIXEL_SIZE + (minimap->tile_size * 2));
	mlx_image_to_window(cub->mlx, cub->minimap_img, pos_x, pos_y);
}
