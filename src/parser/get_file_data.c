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

char	*copy_input_struct(char *source)
{
	char	*tmp;
	int		i;

	tmp = ft_calloc(ft_strlen(source), sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (source[i] && source[i] != '\n')
	{
		tmp[i] = source[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	get_direction_texture_data(t_texture_data *texture_data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' && line[i + 1] == 'O')
			parse_texture(&texture_data->north, line, i + 2);
		else if (line[i] == 'S' && line[i + 1] == 'O')
			parse_texture(&texture_data->south, line, i + 2);
		else if (line[i] == 'W' && line[i + 1] == 'E')
			parse_texture(&texture_data->west, line, i + 2);
		else if (line[i] == 'E' && line[i + 1] == 'A')
			parse_texture(&texture_data->east, line, i + 2);
		else if (line[i] == 'F'
			&& parse_rgb(&texture_data->floor, line, i + 1) == FAILURE)
			return (FAILURE);
		else if (line[i] == 'C'
			&& parse_rgb(&texture_data->ceiling, line, i + 1) == FAILURE)
			return (FAILURE);
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
		if (1 == get_direction_texture_data(&cub->texture_data
				, map_file->textures_path[i]))
			break ;
		i++;
	}
}
