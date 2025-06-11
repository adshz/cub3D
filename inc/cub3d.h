/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:34:54 by aalissa           #+#    #+#             */
/*   Updated: 2025/06/05 16:43:22 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <time.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include "get_next_line.h"
# include "mlx.h"
# include <time.h>
# include "libft.h"

# define RED "\e[31m"
# define YELLOW "\e[33m"
# define RESET "\e[0m"
# define DEBUG_MODE 1
# define WIN_HEIGHT 512
# define WIN_WIDTH 1024
# define TEX_SIZE 64
# define ERR_MALLOC "Could not allocate memory"

enum e_signpost
{
	SUCCESS,
	FAILURE,
	ERR,
	BREAK,
	CONTINUE
};

typedef struct s_map_data
{
	int		fd;
	int		line_count;
	char	*filepath;
	char	**file;
	int		height;
	int		width;
	int		index_end_of_map;
}	t_map_data;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_initial_data_addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_texture_data
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_texture_data;

typedef struct s_minimap
{
	char	**map;
	t_img	*img;
	int		size;
	int		offset_x;
	int		offset_y;
	int		distance;
	int		tile_size;
}	t_minimap;

typedef struct s_ray
{
  double  camera_x;
  double  dir_x;
  double  dir_y;
  int     map_x;
  int     map_y;
  int     step_x;
  int     step_y;
  double  sidedist_x;
  double  sidedist_y;
  double  deltadist_x;
  double  deltadist_y;
  double  wall_dist;
  double  wall_x;
  int     side;
  int     line_height;
  int     draw_start;
  int     draw_end;
} t_ray;

typedef struct s_cub
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				win_height;
	int				win_width;
	t_player		player;
	t_texture_data	texture_data;
  t_ray     ray;
	char			**map_matrix;
	t_map_data		map_data;
	t_img			mlx_img;
	int				**texture_pixels;
	int				**textures;
}	t_cub;

// Old Header need to go through them
typedef struct s_file_input
{
	int		textures_counter;
	int		map_rows;
  //remove map_cols
	int		map_cols;
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

// -----------------------------------------------//
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
void	display_data(t_cub *cub);
int		err_msg(char *msg, char *str, int code);
int		get_total_lines(char *filepath);
void	ft_putstr_fd(char *s, int fd);

#endif
