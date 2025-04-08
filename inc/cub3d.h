/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:34:54 by aalissa           #+#    #+#             */
/*   Updated: 2025/03/07 17:37:16 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "get_next_line.h"
# include "mlx.h"
# include <time.h>

typedef struct s_file_input
{
	int		textures_counter;
	int		map_size;
	char	player_spawn_direction;
	char	**textures_path;
	int		**map;
}	t_file_input;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_flood_fill_data
{
	t_point	*queue;
	int		**map;
	int		*front;
	int		*rear;
	int		size;
}	t_flood_fill_data;

typedef struct s_player_pos
{
	int	player_x_pox;
	int	player_y_pos;
}	t_player_pos;

void	line_check(char *line, int *max);
bool	check_map_enclosed(t_file_input *input, int x, int y);
void	player_pos_init(t_player_pos *player, int x_pos, int y_pos);
void	print_map(int **map, int size);
int		check_map_data_type(char c, t_file_input *input);
void	copy_map(int **src, int ***dest, int size);
void	free_map(int **map, int size);
bool	valid_char(char c);
bool	valid_start_point(char c);
void	last_check(t_file_input *input, t_player_pos *player);
void	print_input(t_file_input *input);
bool	check_extension(char *str);
void	input_obj_init(char *file, t_file_input *input);
void	pars_input(char *v, t_file_input *input);
bool	str_cmp(char *s1, char *s2, int k);
void	texture_assignment(char *line, t_file_input *input);
void	map_assigment(char *line, t_file_input *input);
void	something_went_wrong(char *str, t_file_input *input);
void	free_input(t_file_input *input);

#endif
