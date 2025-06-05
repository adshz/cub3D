/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:38:33 by aalissa           #+#    #+#             */
/*   Updated: 2025/06/05 17:04:40 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_total_lines(char *filepath)
{
	int		fd;
	char	*line;
	int		line_count;

	line = NULL;
	line_count = 0;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		err_msg(filepath, strerror(errno), errno);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
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
}

int	get_columns(char *file)
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
	return (j);
}

void	input_obj_init(char *file, t_file_input *input)
{
	if (!check_extension(file))
		something_went_wrong("Wrong file extension!", NULL);
	input->map_rows = get_total_lines(file);
	input->map_cols = get_columns(file);
	input->textures_counter = 0;
	malloc_obj(input);
}

void	free_input(t_file_input *input)
{
	int	i;

	if (!input)
		return ;
	if (*(input->textures_path) != NULL)
	{
		i = -1;
		while (input->textures_path[++i])
			free(input->textures_path[i]);
		free(input->textures_path);
		input->textures_path = NULL;
	}
	// if (input->map)
	// {
	// 	i = -1;
	// 	while (++i < input->map_rows)
	// 		free(input->map[i]);
	// 	free(input->map);
	// 	input->map = NULL;
	// }
}
