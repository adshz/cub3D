/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:40:14 by aalissa           #+#    #+#             */
/*   Updated: 2025/03/07 17:40:18 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_assignment(char *line, t_file_input *input)
{
	int		i;
	int		j;
	int		k;
	size_t	len;

	i = 0;
	j = 0;
	k = 0;
	len = 0;
	while (input->textures_path[i] != NULL)
		i++;
	if (i >= 6)
		something_went_wrong("Too many textures!", NULL);
	while (line[k] && is_blank(line[k]))
		k++;
	len = ft_strlen(line + k);
	input->textures_path[i] = malloc(sizeof(char) * (len + 1));
	if (!input->textures_path[i])
		something_went_wrong("Memory allocation failed!", NULL);
	while (line[k])
		input->textures_path[i][j++] = line[k++];
	input->textures_path[i][j] = '\0';
}

// delte this
// void	map_assigment(char *line, t_file_input *input)
// {
// 	int	i;
// 	int	j;
// 	int	map_size;
//
// 	i = 0;
// 	map_size = input->map_size;
// 	if (!input || !input->map)
// 		return ;
// 	while (i < map_size && input->map[i] && input->map[i][1] != 21)
// 		++i;
// 	if (i >= map_size || !input->map[i])
// 		return ;
// 	j = 0;
// 	while (line[j] && j < map_size - 1)
// 	{
// 		input->map[i][j + 1] = check_map_data_type(line[j], input);
// 		++j;
// 	}
// 	while (j < map_size - 1)
// 	{
// 		input->map[i][j + 1] = 21;
// 		++j;
// 	}
// 	input->map[i][map_size - 1] = 42;
// }

void	line_assigment(char *line, t_file_input *input)
{
  int i;

  i = 0
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		i++;
  line = line + i;
	if (str_cmp(line, "NO", 2) || str_cmp(line, "SO", 2)
		|| str_cmp(line, "WE", 2) || str_cmp(line, "EA", 2)
		|| str_cmp(line, "F", 1) || str_cmp(line, "C", 1))
	{
		input->textures_counter += 1;
		texture_assignment(line, input);
	}
}

void	pars_input(char *file, t_file_input *input)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_assigment(line, input);
		free(line);
	}
	close(fd);
}
