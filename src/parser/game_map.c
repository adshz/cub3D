/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:41:09 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 17:44:33 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	count_map_lines(t_cub *cub, char **file, int i)
{
	int	start;
	int	j;

	start = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r' \
			|| file[i][j] == '\v' || file[i][j] == '\f')
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	cub->map_data.index_end_of_map = i - get_map_data_location(file);
	return (i - start);
}

static int	get_map_info(t_cub *cub, char **file, int i)
{
	cub->map_data.height = count_map_lines(cub, file, i);
	cub->map_matrix = malloc(sizeof(char *) * (cub->map_data.height + 1));
	if (!cub->map_matrix)
		return (err_msg(NULL, ERR_MALLOC, FAILURE));
	if (fill_map_matrix(&cub->map_data, cub->map_matrix, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	turn_space_to_wall(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map_matrix[i])
	{
		j = 0;
		while (cub->map_matrix[i][j] == ' ' || cub->map_matrix[i][j] == '\t' \
			|| cub->map_matrix[i][j] == '\r' || cub->map_matrix[i][j] == '\v' \
			|| cub->map_matrix[i][j] == '\f')
			j ++;
		while (cub->map_matrix[i][++j])
		{
			if (cub->map_matrix[i][j] == ' ' && \
				j != cub->map_matrix[i][ft_strlen(cub->map_matrix[i]) -1])
				cub->map_matrix[i][j] = '1';
		}
		i++;
	}
}

int	assign_map_data(t_cub *cub, char **map, int i)
{
	if (get_map_info(cub, map, i) == FAILURE)
		return (FAILURE);
	turn_space_to_wall(cub);
	return (SUCCESS);
}

