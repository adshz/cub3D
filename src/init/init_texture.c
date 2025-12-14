/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:40:14 by szhong            #+#    #+#             */
/*   Updated: 2025/06/24 16:50:52 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static uint32_t	get_pixel_color(mlx_texture_t *tex, int x, int y)
{
	uint8_t		*pixel;
	uint32_t	color;

	pixel = &tex->pixels[(y * tex->width + x) * tex->bytes_per_pixel];
	color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | 0xFF;
	return (color);
}

uint32_t	*png_to_buffer(t_cub *cub, char *path)
{
	mlx_texture_t	*tex;
	uint32_t		*buffer;
	int				y;
	int				x;

	tex = mlx_load_png(path);
	if (!tex)
		clean_exit(cub, err_msg(path, "Failed to load PNG texture", FAILURE));
	cub->texture_data.size = tex->width;
	buffer = ft_calloc(tex->width * tex->height, sizeof(uint32_t));
	if (!buffer)
	{
		mlx_delete_texture(tex);
		clean_exit(cub, err_msg(NULL, ERR_MALLOC, FAILURE));
	}
	y = -1;
	while (++y < (int)tex->height)
	{
		x = -1;
		while (++x < (int)tex->width)
			buffer[y * tex->width + x] = get_pixel_color(tex, x, y);
	}
	mlx_delete_texture(tex);
	return (buffer);
}

void	transform_textures(t_cub *cub)
{
	cub->textures = ft_calloc(5, sizeof(uint32_t *));
	if (!cub->textures)
		clean_exit(cub, err_msg(NULL, ERR_MALLOC, FAILURE));
	cub->textures[NORTH] = png_to_buffer(cub, cub->texture_data.north);
	cub->textures[SOUTH] = png_to_buffer(cub, cub->texture_data.south);
	cub->textures[EAST] = png_to_buffer(cub, cub->texture_data.east);
	cub->textures[WEST] = png_to_buffer(cub, cub->texture_data.west);
}

void	init_texture_data(t_texture_data *texture_data)
{
	texture_data->north = NULL;
	texture_data->south = NULL;
	texture_data->east = NULL;
	texture_data->west = NULL;
	texture_data->floor = 0;
	texture_data->ceiling = 0;
	texture_data->hex_ceiling = 0x0;
	texture_data->hex_floor = 0x0;
	texture_data->size = TEX_SIZE;
	texture_data->step = 0.0;
	texture_data->pos = 0.0;
	texture_data->x = 0;
	texture_data->y = 0;
}
