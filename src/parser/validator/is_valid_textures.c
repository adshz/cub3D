/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:30:23 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 17:34:06 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static unsigned long	convert_rgb_to_hex(int *rgb_matrix)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb_matrix[0];
	g = rgb_matrix[1];
	b = rgb_matrix[2];
	result = ((r & 0xff) << 24) | ((g & 0xff) << 16)
		| ((b & 0xff) << 8) | 0xff;
	return (result);
}

int	validate_data(t_cub *cub)
{
	if (is_map_valid(cub, cub->map_matrix) == FAILURE)
		return (free_cub(cub));
	if (is_texture_valid(cub, &cub->texture_data) == FAILURE)
		return (free_cub(cub));
	cub->texture_data.hex_floor = convert_rgb_to_hex(cub->texture_data.floor);
	cub->texture_data.hex_ceiling = convert_rgb_to_hex(
			cub->texture_data.ceiling);
	init_player_direction(cub);
	if (DEBUG_MODE)
		display_data(cub);
	return (SUCCESS);
}

int	parse_rgb(int **target, char *line, int index)
{
	char	*tmp;

	if (!(*target))
	{
		tmp = copy_input_struct(line + get_path_location(line, index));
		*target = configure_rgb(tmp);
		free(tmp);
		if (!(*target))
			return (FAILURE);
	}
	return (SUCCESS);
}

void	parse_texture(char **target, char *line, int index)
{
	if (!(*target))
		*target = copy_input_struct(line + get_path_location(line, index));
}

int	is_texture_valid(t_cub *cub, t_texture_data *textures)
{
	if (!textures->north || !textures->south
		|| !textures->west || !textures->east)
		return (err_msg(cub->map_data.filepath, "Textures missing", FAILURE));
	if (!textures->floor || !textures->ceiling)
		return (err_msg(cub->map_data.filepath, "Colours missing", FAILURE));
	if (is_file_valid(textures->north, false) == FAILURE
		|| is_file_valid(textures->south, false) == FAILURE
		|| is_file_valid(textures->west, false) == FAILURE
		|| is_file_valid(textures->east, false) == FAILURE
		|| is_rgb_valid(textures->floor) == FAILURE
		|| is_rgb_valid(textures->ceiling) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
