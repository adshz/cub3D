/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szhong <szhong@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:22:32 by szhong            #+#    #+#             */
/*   Updated: 2025/06/04 15:31:58 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	debug_print_char_matrix(char **matrix)
{
	int	i;
	
	printf("\n");
	i = 0;
	while (matrix[i])
	{
		printf("%s\n", matrix[i]);
		i++;
	}
	printf("\n");
}

void	debug_display_minimap(t_minimap *minimap)
{
	printf(YELLOW "\n-------- MINIMAP --------\m" RESET);
	printf("Minimap view distance: %d\n", minimap->view_dist);
	printf("Minimap size: %d * %d\n", minimap->size, minimap->size);
	debug_printf_char_tab(minimap->map);
}

void	debug_display_map_data(t_cub *cub)
{
	printf(YELLOW "\n-------- MAP --------\n" RESET);
	printf("Map height: %d\n", cub->map_data.height);
	printf("Map width: %d\n", cub->map_data.width);
	debug_printf_char_matrix(cub->map_matrix);
	printf(YELLOW "\n-------- TEXTURES & COLORS --------\n" RESET);
	printf("Color ceiling #%lx\n", cub->texture_data.hex_ceiling);
	printf("Color floor #%lx\n", cub->texture_data.hex_floor);
	printf("Texture north: %s\n", cub->texture_data.north);
	printf("Texture south: %s\n", cub->texture_data.south);
	printf("Texture east: %s\n", cub->texture_data.east);
	printf("Texture west: %s\n", cub->texture_data.west);
}

void	debug_display_player(t_cub *cub)
{
	printf(YELLOW "\n-------- PLAYER --------\n" RESET);
	printf("Player pos: ");
	printf("x = %f, y = %f\n", cub->player.pos_x, cub->player.pos_y);
	printf("(x = %f, y = %f)\n", cub->player.dir_x, cub->player.dir_y);
}

void	display_data(t_cub *cub)
{
	debug_display_map_data(cub);
	debug_display_player(cub);
	printf("\n");
}
