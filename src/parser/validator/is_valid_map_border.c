/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_border.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:39:37 by szhong            #+#    #+#             */
/*   Updated: 2025/07/04 17:40:17 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static int	check_top_or_bottom(char **map_matrix, int i, int j)
{
	if (!map_matrix || !map_matrix[i] || !map_matrix[i][j])
		return (FAILURE);
	while (map_matrix[i][j] == ' ' || map_matrix[i][j] == '\t' ||
		map_matrix[i][j] == '\r' || map_matrix[i][j] == '\v' ||
		map_matrix[i][j] == '\f')
		j++;
	while (map_matrix[i][j])
	{
		if (map_matrix[i][j] != '1')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

int	check_map_sides(t_map_data *map_data, char **map_matrix)
{
	int	i;
	int	j;

	if (check_top_or_bottom(map_matrix, 0, 0) == FAILURE)
		return (FAILURE);
	i = 1;
	while (i < (map_data->height - 1))
	{
		j = (int)ft_strlen(map_matrix[i]) - 1;
		if (map_matrix[i][j] != '1')
			return (FAILURE);
		i++;
	}
	if (check_top_or_bottom(map_matrix, i, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
