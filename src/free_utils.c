/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:38:33 by aalissa           #+#    #+#             */
/*   Updated: 2025/03/07 17:38:53 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	border_setup(t_file_input *input)
{
	int	i;
	int	j;
	int	map_size;

	map_size = input->map_size;
	j = -1;
	while (++j < map_size)
	{
		input->map[0][j] = 42;
		input->map[map_size - 1][j] = 42;
	}
	i = -1;
	while (++i < map_size)
	{
		input->map[i][0] = 42;
		input->map[i][map_size - 1] = 42;
	}
}

void	map_obj_init(t_file_input	*input)
{
	int	i;
	int	j;
	int	map_size;

	map_size = input->map_size;
	i = -1;
	input->map = malloc(sizeof(int *) * (map_size + 1));
	if (!input->map)
		something_went_wrong("Memory allocation failed for map rows!", NULL);
	while (++i < map_size)
	{
		input->map[i] = malloc(sizeof(int) * map_size);
		if (!input->map[i])
			something_went_wrong("Memory allocation failed for map row!", NULL);
		j = -1;
		while (++j < map_size)
			input->map[i][j] = 21;
	}
	input->map[map_size] = NULL;
	border_setup(input);
}

void	malloc_obj(t_file_input *input)
{
	int	j;

	j = 0;
	input->textures_path = malloc(sizeof(char *) * 7);
	if (!input->textures_path)
		something_went_wrong("Memory allocation failed for textures path!", \
				NULL);
	while (j < 6)
	{
		input->textures_path[j] = NULL;
		++j;
	}
	input->textures_path[6] = NULL;
	map_obj_init(input);
}

void	input_obj_init(char *file, t_file_input *input)
{
	int		j;
	int		fd;
	char	*line;

	j = 0;
	line = NULL;
	if (!check_extension(file))
		something_went_wrong("Wrong file extension!", NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		something_went_wrong("File doesn't exist! Stop trolling, please.", \
				NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!(line))
			break ;
		line_check(line, &j);
		free(line);
	}
	close(fd);
	input->map_size = j + 2;
	input->textures_counter = 0;
	malloc_obj(input);
}

void	free_input(t_file_input *input)
{
	int	i;

	if (!input)
		return ;
	if (input->textures_path)
	{
		i = -1;
		while (input->textures_path[++i])
			free(input->textures_path[i]);
		free(input->textures_path);
		input->textures_path = NULL;
	}
	if (input->map)
	{
		i = -1;
		while (++i < input->map_size)
			free(input->map[i]);
		free(input->map);
		input->map = NULL;
	}
}
