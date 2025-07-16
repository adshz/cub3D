/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:36:25 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 17:38:26 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static int	is_position_valid(t_cub *cub, char **map_matrix)
{
	int	i;
	int	j;

	i = (int)cub->player.pos_y;
	j = (int)cub->player.pos_x;
	if (ft_strlen(map_matrix[i - 1]) < (size_t)j
		|| ft_strlen(map_matrix[i + 1]) < (size_t)j
		|| is_whitespace(map_matrix[i][j - 1]) == SUCCESS
		|| is_whitespace(map_matrix[i][j + 1]) == SUCCESS
		|| is_whitespace(map_matrix[i - 1][j]) == SUCCESS
		|| is_whitespace(map_matrix[i + 1][j]) == SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static void	place_player(t_cub *cub, char **map_matrix)
{
	int	i;
	int	j;

	i = 0;
	while (map_matrix[i])
	{
		j = 0;
		while (map_matrix[i][j])
		{
			if (ft_strchr("NSEW", map_matrix[i][j]))
			{
				cub->player.pos_x = (double)i + 0.5;
				cub->player.pos_y = (double)i + 0.5;
				map_matrix[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

static int	check_player_position(t_cub *cub, char **map_matrix)
{
	if (cub->player.dir == '0')
		return (err_msg(cub->map_data.filepath,
				"Map has no player position (N, S, E, W)", FAILURE));
	place_player(cub, map_matrix);
	if (is_position_valid(cub, map_matrix) == FAILURE)
		return (err_msg(cub->map_data.filepath,
				"Invalid player position", FAILURE));
	return (SUCCESS);
}

static int	check_map_data_position(t_map_data *map_data)
{
	int	i;
	int	j;

	i = map_data->index_end_of_map;
	while (map_data->file[i])
	{
		j = 0;
		while (map_data->file[i][j])
		{
			if (map_data->file[i][j] == ' ' || map_data->file[i][j] == '\t'
				|| map_data->file[i][j] == '\r' || map_data->file[i][j] == '\v'
				|| map_data->file[i][j] == '\f')
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	is_map_valid(t_cub *cub, char **map_matrix)
{
	if (!cub->map_matrix)
		return (err_msg(cub->map_data.filepath, "Map is missing", FAILURE));
	if (check_map_sides(&cub->map_data, map_matrix) == FAILURE)
		return (err_msg(cub->map_data.filepath, "Map has no walls", FAILURE));
	if (cub->map_data.height < 3)
		return (err_msg(cub->map_data.filepath, "Map is too small", FAILURE));
	if (check_map_elements(cub, map_matrix) == FAILURE)
		return (FAILURE);
	if (check_player_position(cub, map_matrix) == FAILURE)
		return (FAILURE);
	if (check_map_data_position(&cub->map_data) == FAILURE)
		return (err_msg(cub->map_data.filepath
				, "Map data is not the end", FAILURE));
	return (SUCCESS);
}
