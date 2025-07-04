/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:51:19 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 17:54:08 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	get_map_data_location(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = get_path_location(map[i], 0);
		if (ft_isdigit(map[i][j]) == 1)
			break ;
		i++;
	}
	return (i);
}

int	get_map_data(t_cub *cub, char **map)
{
	int	i;
	int	j;
	int	ret;

	i = get_map_data_location(map);
	while (map[i])
	{
		cub->map_data.file = cub->map_data.file + i;
		j = get_path_location(map[i], 0);
		while (map[i][j])
		{
			ret = get_valid_data(cub, map, i, j);
			if (ret == FAILURE)
				return (FAILURE);
			else if (ret == SUCCESS)
				return (SUCCESS);
			j ++;
		}
		i++;
	}
	return (ret);
}

int	create_map(t_cub *cub, char **argv)
{
	if (is_file_valid(argv[1], true) == FAILURE)
		clean_exit(cub, FAILURE);
	parse_map_data(argv[1], cub);
	if (get_map_data(cub, cub->map_data.file) == FAILURE)
		return (free_cub(cub));
	if (is_map_valid(cub, cub->map_matrix) == FAILURE)
		return (free_cub(cub));
	init_player_direction(cub);
	if (DEBUG_MODE)
		display_data(cub);
	return (SUCCESS);
}
