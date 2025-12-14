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
# define BONUS 1

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
# include "MLX42/MLX42.h"

/* Key code aliases for compatibility */
# define KEY_ESC MLX_KEY_ESCAPE
# define KEY_W MLX_KEY_W
# define KEY_A MLX_KEY_A
# define KEY_S MLX_KEY_S
# define KEY_D MLX_KEY_D
# define KEY_LEFT MLX_KEY_LEFT
# define KEY_RIGHT MLX_KEY_RIGHT
# include "libft.h"
# include "get_next_line.h"

/* Macros */
# define RED "\e[31m"
# define YELLOW "\e[33m"
# define RESET "\e[0m"
# define WIN_HEIGHT 512
# define WIN_WIDTH 1024
# define TEX_SIZE 64
# define MOVESPEED 0.1
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
# define DIST_EDGE_MOUSE_WRAP 20

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

typedef struct s_file_input
{
	int		textures_counter;
	int		map_rows;
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
	mlx_image_t	*img_ptr;
	uint32_t	*pixels;
	int			width;
	int			height;
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
	mlx_t			*mlx;
	mlx_image_t		*frame;
	int				win_height;
	int				win_width;
	t_player		player;
	t_texture_data	texture_data;
	t_ray			ray;
	char			**map_matrix;
	t_map_data		map_data;
	uint32_t		**texture_pixels;
	uint32_t		**textures;
	mlx_image_t		*minimap_img;
	char			**raw_file;
}	t_cub;

/* Function Prototypes */

/* Parsing */
void	parse_file(char **argv, t_cub *cub, t_file_input *input);
void	parse_map_data(char *filepath, t_cub *cub);
void	assign_texture_data(t_cub *cub, t_file_input *map_file);
void	parse_texture(char **target, char *line, int index);
int		parse_rgb(int **target, char *line, int index);
char	*copy_input_struct(char *source);
void	pars_input(char *file, t_file_input *input);

/* Validation */
int		is_map_valid(t_cub *cub, char **map_matrix);
int		check_map_sides(t_map_data *map_data, char **map_matrix);
int		check_map_elements(t_cub *cub, char **map_matrix);
int		is_file_valid(char *arg, bool is_cub);

/* Rendering */
void	render_game(t_cub *cub);
void	render_wrapper(void *param);
void	render_minimap(t_cub *cub);
void	render_minimap_image(t_cub *cub, t_minimap *minimap);
void	put_pixel(mlx_image_t *img, int x, int y, uint32_t color);

/* Initialization */
void	init_data(t_cub *cub);
void	init_texture_data(t_texture_data *texture_data);
void	init_player_direction(t_cub *cub);
void	init_mlx(t_cub *cub);
void	setup_hooks(t_cub *cub);

/* Raycasting */
int		build_raycasting(t_player *player, t_cub *cub);
void	init_ray(t_ray *ray);
void	update_texture_pixels(t_cub *cub, \
						t_texture_data *texture, t_ray *ray, int x);

/* Textures */
int		is_texture_valid(t_cub *cub, t_texture_data *textures);
int		*configure_rgb(char *line);
int		is_rgb_valid(int *rgb);
void	init_texture_pixels(t_cub *cub);

/* Utilities */
void	*ft_calloc(size_t nmemb, size_t size);
void	free_matrix(void **matrix);
void	display_data(t_cub *cub);
void	fill_matrix(int row, int column, int i, t_cub *cub);
void	free_input(t_file_input *input);
void	assign_data(t_cub *cub, t_file_input *input);
void	transform_textures(t_cub *cub);
void	event_listening(t_cub *cub);
void	line_check(char *line, int *max);
bool	str_cmp(char *s1, char *s2, int k);
bool	check_extension(char *str);
int		get_path_location(char *line, int i);
int		get_valid_data(t_cub *cub, char **map, int i, int j);
int		err_msg(char *msg, char *str, int code);
void	print_usage(void);
int		is_whitespace(char c);
int		get_total_lines(char *filepath);
int		validate_data(t_cub *cub);
int		quit_game(t_cub *cub);

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

/* libft */
void	*ft_memset(void *s, int c, size_t n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

/* extra */
void	input_obj_init(char *file, t_file_input *input);
void	something_went_wrong(char *str, t_file_input *input);

#endif
