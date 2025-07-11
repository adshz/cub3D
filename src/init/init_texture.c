/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:40:14 by szhong            #+#    #+#             */
/*   Updated: 2025/06/24 16:50:52 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	*xpm_to_img(t_cub *cub, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		y;
	int		x;

	init_texture_img(cub, &tmp, path);
	buffer = ft_calloc(1,
			sizeof * buffer * cub->texture_data.size * cub->texture_data.size);
	if (!buffer)
		clean_exit(cub, err_msg(NULL, ERR_MALLOC, 1));
	y = 0;
	while (y < cub->texture_data.size)
	{
		x = 0;
		while (x < cub->texture_data.size)
		{
			buffer[y * cub->texture_data.size + x]
				= tmp.img_initial_data_addr[y * cub->texture_data.size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(cub->mlx_ptr, tmp.img_ptr);
	return (buffer);
}

void	transform_textures(t_cub *cub)
{
	cub->textures = ft_calloc(5, sizeof * cub->textures);
	if (!cub->textures)
		clean_exit(cub, err_msg(NULL, ERR_MALLOC, 1));
	cub->textures[NORTH] = xpm_to_img(cub, cub->texture_data.north);
	cub->textures[SOUTH] = xpm_to_img(cub, cub->texture_data.south);
	cub->textures[EAST] = xpm_to_img(cub, cub->texture_data.east);
	cub->textures[WEST] = xpm_to_img(cub, cub->texture_data.west);
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
