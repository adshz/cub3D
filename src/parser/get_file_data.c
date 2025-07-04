/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:45:03 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 17:47:16 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	get_path_location(char *line, int i)
{
	while (is_whitespace(line[i]) == SUCCESS)
		i++;
	return (i);
}

int	get_direction_texture_data(t_texture_data *texture_data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' && line[i + 1] == 'O' && !(texture_data->north))
			texture_data->north = line + get_path_location(line, i + 2);
		else if (line[i] == 'S' && line[i + 1] == 'O' && !(texture_data->south))
			texture_data->south = line + get_path_location(line, i + 2);
		else if (line[i] == 'W' && line[i + 1] == 'E' && !(texture_data->west))
			texture_data->west = line + get_path_location(line, i + 2);
		else if (line[i] == 'E' && line[i + 1] == 'A' && !(texture_data->east))
			texture_data->east = line + get_path_location(line, i + 2);
		else if (!texture_data->floor && line[i] == 'F')
		{
			texture_data->floor = configure_rgb(line + get_path_location(line, i + 1));
			if (texture_data->floor == NULL)
				return (FAILURE);
		}
		else if (!texture_data->ceiling && line[i] == 'C')
		{
			texture_data->ceiling = configure_rgb(line + i + get_path_location(line, i + 1));
			if (texture_data->ceiling == NULL)
				return (FAILURE); 
		}
		i++;
	}
	return (SUCCESS);
}

void	assign_texture_data(t_cub *cub, t_file_input *map_file)
{
	int	i;

	i = 0;
	while (map_file->textures_path[i])
	{
		if (1 == get_direction_texture_data(&cub->texture_data, map_file->textures_path[i]))
			break ;
		i++;
	}
}

