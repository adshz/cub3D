/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:41:18 by aalissa           #+#    #+#             */
/*   Updated: 2025/06/05 16:32:21 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_input(t_file_input *input)
{
	int	i;
	int	j;

	if (!input)
	{
		printf("Input is NULL!\n");
		return ;
	}
	printf("Textures Paths: raw data as follows\n");
	i = -1;
	while (input->textures_path[++i])
		printf("  [%d]: here======================= %s\n", i, input->textures_path[i]);
	printf("\nMap: Raw Data as follows:\n");
	i = -1;
	while (input->map[++i])
	{
		printf("Row: faw data as follows:");
		j = -1;
		while (++j < input->map_cols)
			printf("%d ", input->map[i][j]);
		printf("\n");
	}
}

void	print_map(int **map, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			printf("%d  ", map[i][j]);
		printf("\n");
	}
}
