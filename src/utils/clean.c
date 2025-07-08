/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:30:31 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 16:45:02 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	clean_exit(t_cub *cub, int code)
{
	if (!cub)
		exit(code);
	if (cub->win_ptr && cub->mlx_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	if (cub->mlx_ptr)
	{
		mlx_destroy_display(cub->mlx_ptr);
		mlx_loop_end(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
	free_cub(cub);
	exit(code);
}

void	free_matrix(void **matrix)
{
	size_t	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	if (matrix)
	{
		free(matrix);
		matrix = NULL;
	}
}

void	free_map_data(t_cub *cub)
{
	if (cub->map_data.fd > 0)
		close(cub->map_data.fd);
	if (cub->raw_file)
		free_matrix((void **)cub->raw_file);
	if (cub->map_matrix)
		free_matrix((void **)cub->map_matrix);
}

void	free_texture_data(t_texture_data *texture_data)
{
	if (texture_data->north != NULL)
		free(texture_data->north);
	if (texture_data->south != NULL)
		free(texture_data->south);
	if (texture_data->east != NULL)
		free(texture_data->east);
	if (texture_data->west != NULL)
		free(texture_data->west);
	if (texture_data->floor)
		free(texture_data->floor);
	if (texture_data->ceiling)
		free(texture_data->ceiling);
}

int	free_cub(t_cub *cub)
{
	if (cub->textures)
		free_matrix((void **)cub->textures);
	if (cub->texture_pixels)
		free_matrix((void **)cub->texture_pixels);
	free_texture_data(&cub->texture_data);
	free_map_data(cub);
	return (FAILURE);
}
