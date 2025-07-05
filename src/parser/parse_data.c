/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:51:59 by szhong            #+#    #+#             */
/*   Updated: 2025/06/24 16:53:24 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	fill_map_matrix(t_map_data *map_data, char **map_matrix, int index)
{
	int	i;
	int	j;

	i = 0;
	map_data->width = find_biggest_len(map_data, i);
	while (i < map_data->height)
	{
		j = 0;
		map_matrix[i] = malloc(sizeof(char) * (map_data->width + 1));
		if (!map_matrix[i])
			return (err_msg(NULL, ERR_MALLOC, FAILURE));
		while (map_data->file[i][j] && map_data->file[i][j] != '\n')
		{
			map_matrix[i][j] = map_data->file[i][j];
			j++;
		}
		while (j < map_data->width)
			map_matrix[i][j++] = '\0';
		i++;
		index++;
	}
	map_matrix[i] = NULL;
	return (SUCCESS);
}

void	parse_map_data(char *filepath, t_cub *cub)
{
	int		row;
	int		i;
	size_t	col;

	i = 0;
	row = 0;
	col = 0;
	cub->map_data.line_count = get_total_lines(filepath);
	cub->map_data.filepath = filepath;
	cub->map_data.file = ft_calloc(cub->map_data.line_count + 1, sizeof(char *));
	if (!(cub->map_data.file))
	{
		err_msg(NULL, "Failed to allocate memory", FAILURE);
		return ;
	}
	cub->map_data.fd = open(filepath, O_RDONLY);
	if (cub->map_data.fd < 0)
		err_msg(filepath, strerror(errno), FAILURE);
	else
	{
		fill_matrix(row, col, i, cub);
		close(cub->map_data.fd);
	}
}
