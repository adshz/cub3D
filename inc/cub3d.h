/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:34:54 by aalissa           #+#    #+#             */
/*   Updated: 2025/07/04 18:19:34 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define BONUS 1
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
# include <X11/keysym.h>
# include <X11/X.h>

# define RED "\e[31m"
# define YELLOW "\e[33m"
# define RESET "\e[0m"
# define DEBUG_MODE 1
# define WIN_HEIGHT 512
# define WIN_WIDTH 1024
# define TEX_SIZE 64
# define MOVESPEED 0.0125
# define ROTSPEED 0.015
# define ERR_MALLOC "Could not allocate memory"
# define DIST_EDGE_MOUSE_WRAP 20
# define MINIMAP_PIXEL_SIZE 128
# define MINIMAP_VIEW_DIST 4
# define MINIMAP_COLOR_PLAYER 0x00FF00
# define MINIMAP_COLOR_WALL 0x808080
# define MINIMAP_COLOR_FLOOR 0xE6E6E6
# define MINIMAP_COLOR_SPACE 0x404040
# define MINIMAP_DEBUG_MODE 0

enum	e_signpost
{
	SUCCESS,
	FAILURE,
	ERR,
	BREAK,
	CONTINUE
};

enum	e_texture_index
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

typedef	struct s_map_data
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
	t_ray			ray;
	char			**map_matrix;
	t_map_data		map_data;
	t_img			mlx_img;
	int				**texture_pixels;
	int				**textures;
	t_img			minimap;
	char			**raw_file;
}	t_cub;

// Old Header need to go through them
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
void	init_img(t_cub *cub, t_img *img, int width, int height);
void	init_ray(t_ray *ray);
void	init_map_data(t_map_data *map_data);
void	init_player_direction(t_cub *cub);
void	init_data(t_cub *cub);
void	init_texture_data(t_texture_data *texture_data);
void	transform_textures(t_cub *cub);
int		*xpm_to_img(t_cub *cub, char *path);
void	init_mlx_img(t_img *mlx_img);
void	init_texture_img(t_cub *cub, t_img *image, char *filepath);
void	init_img(t_cub *cub, t_img *img, int width, int height);
void	clean_exit(t_cub *cub, int code);
void	*ft_calloc(size_t nmemb, size_t size);
int		fill_map_matrix(t_map_data *map_data, char **map_matrix, int index);
int		is_whitespace(char c);
void	parse_map_data(char *filepath, t_cub *cub);
void	render_game(t_cub *cub);
int		render_wrapper(t_cub *cub);
int		build_raycasting(t_player *player, t_cub *cub);
void	init_texture_pixels(t_cub *cub);
void	update_texture_pixels(t_cub *cub, t_texture_data *texture, t_ray *ray, int x);
void	set_image_pixel(t_img *image, int x, int y, int color);
void	render_minimap(t_cub *cub);
void	event_listening(t_cub *cub);
int		move_player(t_cub *cub);
int		validate_move(t_cub *cub, double new_x, double new_y);
void	free_matrix(void **matrix);
int		free_cub(t_cub *cub);
void	free_map_data(t_cub *cub);
void	free_texture_data(t_texture_data *texture_data);
int		move_around(t_cub *cub, double rotdir);
int		is_file_valid(char *arg, bool is_cub);
int		is_map_valid(t_cub *cub, char **map_matrix);
int		check_map_sides(t_map_data *map_data, char **map_matrix);
int		count_map_lines(t_cub *cub, char **file, int i);
int		get_direction_texture_data(t_texture_data *texture_data, char *line);
void	assign_texture_data(t_cub *cub, t_file_input *map_file);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putnbr_fd(int n, int fd);
int		is_rgb_valid(int *rgb);
int		*configure_rgb(char *line);
int		get_valid_data(t_cub *cub, char **map, int i, int j);
void	fill_matrix(int row, int column, int i, t_cub *cub);
void	init_mlx(t_cub *cub);
void	parse_file(char **argv, t_cub *cub, t_file_input *input);
void	assign_data(t_cub *cub, t_file_input *input);
int		get_map_data(t_cub *cub, char **map);
size_t	find_biggest_len(t_map_data *map_data, int i);
int		is_texture_valid(t_cub *cub, t_texture_data *textures);
int		validate_data(t_cub *cub);
unsigned long	convert_rgb_to_hex(int *rgb_matrix);
int		quit_game(t_cub *cub);
void	debug_display_minimap(t_minimap *minimap);
void	render_minimap_image(t_cub *cub, t_minimap *minimap);
void	debug_display_minimap(t_minimap *minimap);
void	debug_print_char_matrix(char **matrix);
void	debug_display_minimap(t_minimap *minimap);
void	debug_display_map_data(t_cub *cub);
void	debug_display_player(t_cub *cub);
void	display_data(t_cub *cub);
int		assign_map_data(t_cub *cub, char **map, int i);
int		get_path_location(char *line, int i);
int		get_map_data_location(char **map);

#endif
