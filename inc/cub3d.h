/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:34:54 by aalissa           #+#    #+#             */
/*   Updated: 2025/07/15 18:45:00 by aalissa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* Libraries */
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

/* Macros */
# define RED "\e[31m"
# define YELLOW "\e[33m"
# define RESET "\e[0m"
# define WIN_HEIGHT 512
# define WIN_WIDTH 1024
# define TEX_SIZE 64
# define MOVESPEED 0.3
# define ROTSPEED 0.015
# define ERR_MALLOC "Could not allocate memory"
# define MINIMAP_PIXEL_SIZE 128
# define MINIMAP_VIEW_DIST 4
# define MINIMAP_COLOR_PLAYER 0x00FF00
# define MINIMAP_COLOR_WALL 0x808080
# define MINIMAP_COLOR_FLOOR 0xE6E6E6
# define MINIMAP_COLOR_SPACE 0x404040
# define MINIMAP_DEBUG_MODE 0
# define DEBUG_MODE 1

/* Enums */
enum e_signpost
{
	SUCCESS,
	FAILURE,
	ERR,
	BREAK,
	CONTINUE
};

enum e_texture_index
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

/* Structs */
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
	int		*img_initial_data_addr;
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
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_cub
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				win_height;
	int				win_width;
	t_player		player;
	t_texture_data	texture_data;
	t_ray			ray;
	char			**map_matrix;
	t_map_data		map_data;
	t_img			mlx_img;
	int				**texture_pixels;
	int				**textures;
	t_img			minimap;
	char			**raw_file;
}	t_cub;

/* Function Prototypes */

/* Parsing */
void	parse_file(char **argv, t_cub *cub, void *input);
void	parse_map_data(char *filepath, t_cub *cub);
void	assign_texture_data(t_cub *cub, void *map_file);
void	parse_texture(char **target, char *line, int index);
int		parse_rgb(int **target, char *line, int index);
char	*copy_input_struct(char *source);

/* Validation */
int		is_map_valid(t_cub *cub, char **map_matrix);
int		check_map_sides(t_map_data *map_data, char **map_matrix);
int		check_map_elements(t_cub *cub, char **map_matrix);
int		is_file_valid(char *arg, bool is_cub);

/* Rendering */
void	render_game(t_cub *cub);
int		render_wrapper(t_cub *cub);
void	render_minimap(t_cub *cub);
void	render_minimap_image(t_cub *cub, t_minimap *minimap);
void	set_image_pixel(t_img *image, int x, int y, int color);

/* Initialization */
void	init_data(t_cub *cub);
void	init_img(t_cub *cub, t_img *img, int width, int height);
void	init_texture_data(t_texture_data *texture_data);
void	init_player_direction(t_cub *cub);
void	init_mlx(t_cub *cub);

/* Raycasting */
int		build_raycasting(t_player *player, t_cub *cub);

/* Utilities */
void	*ft_calloc(size_t nmemb, size_t size);
void	free_matrix(void **matrix);
int		err_msg(char *msg, char *str, int code);
unsigned long	convert_rgb_to_hex(int *rgb_matrix);

/* Movement */
int		move_player(t_cub *cub);
int		validate_move(t_cub *cub, double new_x, double new_y);
int		move_around(t_cub *cub, double rotdir);

/* Debugging */
void	debug_display_minimap(t_minimap *minimap);
void	debug_display_map_data(t_cub *cub);
void	debug_display_player(t_cub *cub);
void	debug_print_char_matrix(char **matrix);

/* Map Handling */
int		fill_map_matrix(t_map_data *map_data, char **map_matrix, int index);
int		assign_map_data(t_cub *cub, char **map, int i);
int		get_map_data(t_cub *cub, char **map);
int		get_map_data_location(char **map);
size_t	find_biggest_len(t_map_data *map_data, int i);

/* Minimap Logic */
char	get_minimap_char(t_cub *cub, int map_x, int map_y);
char	**generate_minimap(t_cub *cub, t_minimap *minimap);
int		get_minimap_offset(t_minimap *minimap, int mapsize, int pos);
bool	is_valid_map_coord(int coord, int size);

/* Cleanup */
void	clean_exit(t_cub *cub, int code);
int		free_cub(t_cub *cub);
void	free_map_data(t_cub *cub);
void	free_texture_data(t_texture_data *texture_data);

#endif
