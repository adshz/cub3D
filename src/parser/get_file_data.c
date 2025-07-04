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


int	get_direction_texture_data(t_texture_data *texture_data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' && line[i + 1] == 'O' && !(texture_data->north))
			texture_data->north = line + 3;
		else if (line[i] == 'S' && line[i + 1] == 'O' && !(texture_data->south))
			texture_data->south = line + 3;
		else if (line[i] == 'W' && line[i + 1] == 'E' && !(texture_data->west))
			texture_data->west = line + 3;
		else if (line[i] == 'E' && line[i + 1] == 'A' && !(texture_data->east))
			texture_data->east = line + 3;
		else if (!texture_data->floor && line[i] == 'F')
		{
			texture_data->floor = configure_rgb(line + i + 2);
			if (texture_data->floor == NULL)
				return (1);
		}
		else if (!texture_data->ceiling && line[i] == 'C')
		{
			texture_data->ceiling = configure_rgb(line + i + 2);
			if (texture_data->ceiling == NULL)
				return (1); 
		}
		i++;
	}
	return (0);
}

void	assign_texture_data(t_cub *cub, t_file_input *map_file)
{
	int	i;

	i = -1;
	while (map_file->textures_path[++i])
	{
		if (1 == get_direction_texture_data(&cub->texture_data, map_file->textures_path[i]))
			break ;
	}
}

