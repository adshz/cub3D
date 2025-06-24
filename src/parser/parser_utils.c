/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:54:21 by szhong            #+#    #+#             */
/*   Updated: 2025/06/24 16:54:59 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

size_t	find_biggest_len(t_map_data *map_data, int i)
{
	size_t	biggest_len;

	biggest_len = ft_strlen(map_data->file[i]);
	while (map_data->file[i])
	{
		if (ft_strlen(map_data->file[i]) > biggest_len)
			biggest_len = ft_strlen(map_data->file[i]);
		i++;
	}
	return (biggest_len);
}

int	is_whitespace(char c)
{
	if (c != ' ' && c != '\t' && c != '\r' && c != '\n' \
		&& c != '\v' && c != '\f')
		return (FAILURE);
	return (SUCCESS);
}
