/* ************************************************************************** */
/*                                                                            */
/*                                                    :::      ::::::::       */
/*   map_elem.c                                		 :+:      :+:    :+:      */
/*                                                  +:+ +:+         +:+       */
/*   By: alissa <aalissa@student.42london.com>     +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:00:00 by alissa            #+#    #+#             */
/*   Updated: 2025/07/15 20:00:00 by alissa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	skip_whitespace(const char *line, int *j)
{
	while (line[*j] == ' ' || line[*j] == '\t'
		|| line[*j] == '\r' || line[*j] == '\v'
		|| line[*j] == '\f')
		(*j)++;
}

static int	validate_map_char(t_cub *cub, char c)
{
	if (!ft_strchr("10NSEW", c))
		return (err_msg(cub->map_data.filepath,
				"Invalid character in map", FAILURE));
	return (SUCCESS);
}

static int	handle_player(t_cub *cub, char c)
{
	if (ft_strchr("NSEW", c))
	{
		if (cub->player.dir != '0')
			return (err_msg(cub->map_data.filepath,
					"Only one player is allowed", FAILURE));
		cub->player.dir = c;
	}
	return (SUCCESS);
}

int	check_map_elements(t_cub *cub, char **map_matrix)
{
	int	i;
	int	j;

	i = 0;
	cub->player.dir = '0';
	while (map_matrix[i] != NULL)
	{
		j = 0;
		while (map_matrix[i][j])
		{
			skip_whitespace(map_matrix[i], &j);
			if (validate_map_char(cub, map_matrix[i][j]) == FAILURE)
				return (FAILURE);
			if (handle_player(cub, map_matrix[i][j]) == FAILURE)
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
