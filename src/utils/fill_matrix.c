/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:57:15 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 17:58:25 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	fill_matrix(int row, int column, int i, t_cub *cub)
{
	char	*line;

	line = get_next_line(cub->map_data.fd);
	while (line != NULL)
	{
		cub->map_data.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!(cub->map_data.file[row]))
		{
			err_msg(NULL, "Failed to allocate memory", FAILURE);
			return (free_matrix((void **)cub->map_data.file));
		}
		while (line[i] != '\0')
			cub->map_data.file[row][column++] = line[i++];
		cub->map_data.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(cub->map_data.fd);
	}
	cub->map_data.file[row] = NULL;
}

int	get_valid_data(t_cub *cub, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
		j++;
	if (ft_isdigit(map[i][j]))
	{
		if (assign_map_data(cub, map, i) == FAILURE)
			return (err_msg(cub->map_data.filepath, \
				"Please check if map description is wrong or incomplete", \
				FAILURE));
		return (SUCCESS);
	}
	return (CONTINUE);
}
