/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:39:42 by aalissa           #+#    #+#             */
/*   Updated: 2025/06/04 15:34:09 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

#define WIN_HEIGHT 512
#define WIN_WIDTH 1024
#define TEX_SIZE 64

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

typedef struct s_cub
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				win_height;
	int				win_width;
	t_player		player;
	t_texture_data	texture_data;
	char			**map_matrix;
	t_map_data		map_data;
	t_img			mlx_img;
	int				**texture_pixels;
	int				**textures;
}	t_cub;

void	init_map_data(t_map_data *map_data)
{
	map_data->fd = 0;
	map_data->line_count = 0;
	map_data->filepath = NULL;
	map_data->file = NULL;
	map_data->height = 0;
	map_data->width = 0;
	map_data->index_end_of_map = 0;
}

void	free_map_data(t_cub *cub)
{
	if (cub->map_data.fd > 0)
		close(cub->map_data.fd);
	if (cub->map_data.file)
		free_matrix((void **)cub->map_data.file);
	if (cub->map_matrix)
		free_matrix((void **)cub->map_matrix);
}

void	init_player(t_player *player)
{
	player->dir = '\0';
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->has_moved = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->rotate = 0;
}

void	init_texture_data(t_texture_data *texture_data)
{
	texture_data->north = NULL;
	texture_data->south = NULL;
	texture_data->east = NULL;
	texture_data->west = NULL;
	texture_data->floor = 0;
	texture_data->ceiling = 0;
	texture_data->hex_ceiling = 0x0;
	texture_data->hex_floor = 0x0;
	texture_data->size = TEX_SIZE;
	texture_data->step = 0.0;
	texture_data->pos = 0.0;
	texture_data->x = 0;
	texture_data->y = 0;
}

void	free_texture_data(t_texture_data *texture_data)
{
	if (texture_data->north != NULL)
		free(texture_data->north);
	if (texture_data->south != NULL)
		free(texture_data->south);
	if (texture_data->east != NULL)
		free(texture_data->east);
	if (texture_data->west != NULL)
		free(texture_data->west);
	if (texture_data->floor)
		free(texture_data->floor);
	if (texture_data->ceiling)
		free(texture_data->ceiling);
}

void	init_mlx_img(t_img *mlx_img)
{
	mlx_img->img_ptr = NULL;
	mlx_img->img_initial_data_addr = NULL;
	mlx_img->bpp = 0;
	mlx_img->size_line = 0;
	mlx_img->endian = 0;
}

void	init_data(t_cub *cub)
{
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->win_height = WIN_HEIGHT;
	cub->win_width = WIN_WIDTH;
	init_player(&cub->player);
	init_texture_data(&cub->texture_data);
	cub->map_matrix = NULL;
	init_map_data(&cub->map_data);
	init_mlx_img(&cub->mlx_img);
	cub->texture_pixels = NULL;
	cub->textures = NULL;
	return ;
}

void	init_game(t_cub *cub)
{
	init_data(cub);
	return ;
}

void	free_matrix(void **matrix)
{
	size_t	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	if (matrix)
	{
		free(matrix);
		matrix = NULL;
	}
}

int	*convert_rgb_type(char **rgb_matrix, int *rgb)
{
	int	i;

	i = 0;
	while (rgb_matrix[i])
	{
		rgb[i] = ft_atoi(rgb_matrix[i]);
		if (rgb[i] == -1)
		{
			free_matrix((void **)rgb_matrix);
			free(rgb);
			return (0);
		}
		i++;
	}
	free_matrix((void **)rgb_matrix);
	return (rgb);
}

bool	check_has_no_digit(char **rgb_matrix)
{
	bool	has_no_digit;
	int		i;
	int		j;
	char	*nbr;

	i = 0;
	has_no_digit = false;
	while (rgb_matrix[i])
	{
		j = 0;
		nbr = ft_strtrim(rgb_matrix[i], "\n");
		while (nbr[j])
		{
			if (ft_isdigit(nbr[j]) == 0)
			{
				has_no_digit = true;
				break ;
			}
			j++;
		}
		i++;
	}
	if (has_no_digit)
		return (true);
	return (false);
}

int	*configure_rgb(char *line)
{
	char	**rgb_split;
	int		*rgb;
	int		num;

	rgb_split = ft_split(line, ',');
	num = 0;
	while (rgb_split[num])
		num++;
	if (num != 3 || check_has_no_digit(rgb_split))
	{
		free_matrix((void **)rgb_split);
		return (0);
	}
	rgb = (int *)malloc(sizeof(int) * 3);
	if (!rgb)
		return (NULL);
	return (convert_rgb_type(rgb_split, rgb));

}

int	get_direction_texture_data(t_texture_data *texture_data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' && line[i + 1] == 'O' && !(texture_data->north))
			texture_data->north = line + 3;
		else if (line[i] == 'S' && line[i + 1] == 'O' && !(texture_data->south))
			texture_data->south = line + 3;
		else if (line[i] == 'W' && line[i + 1] == 'E' && !(texture_data->west))
			texture_data->west = line + 3;
		else if (line[i] == 'E' && line[i + 1] == 'A' && !(texture_data->east))
			texture_data->east = line + 3;
		else if (!texture_data->floor && line[i] == 'F')
		{
			texture_data->floor = configure_rgb(line + i + 2);
			// if (texture_data->floor == NULL)
			// 	return (1); // #TODO: error message and clean
		}
		else if (!texture_data->ceiling && line[i] == 'C')
		{
			texture_data->ceiling = configure_rgb(line + i + 2);
			// if (texture_data->ceiling == NULL)
			// 	return (1); // #TODO: error message and clean
		}
		i++;
	}
	// I think I should write something to prevent error from happening??
	return (0);
}

void	assign_texture_data(t_cub *cub, t_file_input *map_file)
{
	int	i;
	// int	j;

	i = -1;
	while (map_file->textures_path[++i])
	{
		if (1 == get_direction_texture_data(&cub->texture_data, map_file->textures_path[i]))
			break ;
	}
	// next step is to make assign_map_data
}

enum e_signpost
{
	SUCCCESS,
	FAILURE,
	ERR,
	BREAK,
	CONTINUE
};

# define DEBUG_MODE 1


# define RED "\e[31m"
# define RESET "\e[0m"

bool	is_dir(char *arg)
{
	int		fd;

	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (true);
	}
	return (false);
}

bool	is_cub_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u' || arg[len - 1] != 'b' || \
	 arg[len - 4] != '.'))
		return (false);
	return (true);
}

bool	is_xpm_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'x' || arg[len - 2] != 'p' || arg[len - 1] != 'm' || \
	 arg[len - 4] != '.'))
		return (false);
	return (true);
}

int	err_msg(char *msg, char *str, int code)
{
	ft_putstr_fd(RED, "cub3D: Error", 2);
	if (msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n", RESET, 2);
	return (code);
}

int	is_file_valid(char *arg, bool is_cub)
{
	int	fd;

	if (is_dir(arg))
		return (err_msg(arg, "is a directory", FAILURE));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (err_msg(arg, sterror(errno), FAILURE));
	close(fd);
	if (is_cub && !is_cub_file(arg))
		return (err_msg(arg, "is not a .cub file", FAILURE));
	if (!is_cub && is_xpm_file(arg))
		return (err_msg(arg, "is not a .xpm file", FAILURE));
	return (SUCCESS);
}

int	free_cub(t_cub *cub)
{
	if (cub->textures)
		free_matrix((void **)cub->textures);
	if (cub->texture_pixels)
		free_matrix((void **)cub->texture_pixels));
	free_texture_data(&cub->texture_data);
	free_map_data(cub);
	return (FAILURE);
}

void	clean_exit(t_cub *cub, int code)
{
	if (!cub)
		exit(code);
	if (cub->win_ptr && cub->mlx_ptr)
		mlx_destory_window(cub->mlx_ptr, cub->win_ptr);
	if (cub->mlx_tr)
	{
		mlx_destory_display(cub->mlx_ptr);
		mlx_loop_end(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
	free_cub(cub);
	exit(code);
}

int	get_total_lines(char *filepath)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		err_msg(filepath, strerror(errno), errno);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}

//TODO ft_calloc 
//
void	fill_matrix(int row, int column, int i, t_cub *cub)
{
	char	*line;

	line = get_next_line(cub->map_data.fd);
	while (line != NULL)
	{
		cub->map_data.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!(cub->map_data.file[row]))
		{
			err_msg(NULL, "Failed to allocate memory", FAILURE);
			return (free_matrix((void **)cub->map_data.file));
		}
		while (line[i] != '\0')
			cub->map_data.file[row][column++] = line[i++];
		cub->map_data.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(cub->map_data.fd);
	}
	cub->map_data.file[row] = NULL;
}

void	parse_map_data(char *filepath, t_cub *cub)
{
	int		row;
	int		i;
	size_t	col;

	i = 0;
	row = 0;
	col = 0;
	cub->map_data.line_count = get_total_lines(filepath);
	cub->map_data.filepath = filepath;
	cub->map_data.file = ft_calloc(cub->map_data.line_count + 1, sizeof(char *));
	if (!(cub->map_data.file))
	{
		err_msg(NULL, "Failed to allocate memory", FAILURE)
		return ;
	}
	cub->map_data.fd = open(filepath, O_RDONLY);
	if (cub->map_data.fd < 0)
		err_msg(filepath, strerror(errno), FAILURE);
	else
	{
		fill_matrix(row, column, i, cub);
		close(cub->map_data.fd);
	}
}

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

int	fill_map_matrix(t_map_data *map_data, char **map_matrix, int index)
{
	int	i;
	int	j;

	map_data->width = find_biggest_len(map_data, index);
	i = 0;
	while (i < map_data->height)
	{
		j = 0;
		map_matrix[i] = malloc(sizeof(char) * (map_data->width + 1));
		if (!map_matrix[i])
			return (err_msg(NULL, ERR_MALLOC, FAILURE);
		while (map_data->file[index][j] && map_data->file[index[j] != '\n')
		{
			map_data[i][j] = map_data->file[index][j];
			j++;
		}
		while (j < map_data->width)
			map_data[i][j++] = '\0';
		i++;
		index++;
	}
	map_matrix[i] = NULL;
	return (SUCCESS);
}

int	get_map_info(t_cub *cub, char **file, int i)
{
	cub->map_data.height = count_map_lines(cub, file, i);
	cub->map_matrix = malloc(sizeof(char *) * (cub->map_data.height + 1));
	if (!cub->map_matrix)
		return (err_msg(NULL, ERR_MALLOC, FAILURE);
	if (fill_map_matrix(&cub->map_data, cub->map_matrix, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	turn_space_to_wall(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->map_matrix[i])
	{
		j = 0;
		while (cub->map_matrix[i][j] == ' ' || cub->map_matrix[i][j] == '\t' \
			|| cub->map_matrix[i][j] == '\r' || cub->map_matrix[i][j] == '\v' \
			|| cub->map_matrix[i][j] == '\f')
			j ++;
		while (cub->map_matrix[i][++j])
		{
			if (cub->map_matrix[i][j] == ' ' && \
				j != cub->map_matrix[i][ft_strlen(cub->map_matrix[i]) -1])
				cub->map_matrix[i][j] = '1';
		}
		i++;
	}
}

int	assign_map_data(t_cub *cub, char **map, int i)
{
	if (get_map_info(cub, map, i) == FAILURE)
		return (FAILURE);
	turn_space_to_wall(cub);
	return (SUCCESS);
}

int	get_valid_data(t_cub *cub, char **map, int i, int j)
{
	while (map[i][j] == ' ' || map[i][j] == '\t' || map[i][j] == '\n')
		j++;
	if (ft_isdigit(map[i][j])
	{
		if (assign_map_data(cub, map, i) == FAILURE)
			return (err_msg(cub->map_data.filepath, \
				"Please check if map description is wrong or incomplete", \
				FAILURE);
		return (SUCCESS);
	}
	return (CONTINUE);
}

int	get_map_data(t_cub *cub, char **map)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ret = get_valid_data(cub, map, i, j);
			if (ret == FAILURE)
				return (FAILURE);
			else if (ret == SUCCESS)
				return (SUCESS);
			j ++;
		}
		i++;
	}
}

int	check_top_or_bottom(char *map_matrix, int i, int j)
{
	if (!map_matrix || !map_matrix[i] || !map_matrix[i][j])
		return (FAILURE);
	while (map_matrix[i][j] == ' ' || map_matrix[i][j] == '\t' || \
		map_matrix[i][j] == '\r' || map_matrix[i][j] '\v' || \
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
		j = ft_strlen(map_matrix[i]) - 1;
		if (map_matrix[i][j] != '1')
			return (FAILURE);
		i++;
	}
	if (check_top_or_bottom(map_matrix, i, 0) == FAILURE)
		return (FAILURE);
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
			while (map_matrix[i][j] == ' ' || map_matrix[i][j] == '\t' || \
				map_matrix[i][j] == '\r' || map_matrix[i][j] '\v' || \
				map_matrix[i][j] == '\f')
				j++;
			if (!(ft_strchr("10NSEW", map_matrix[i][j])))
				return (err_msg(cub->map_data.filepath, \
					"Invalid character in map", FAILURE));
			if (ft_strchr("NSEW", map_matrix[i][j]) && cub->player.dir != '0')
				return (err_msg(cub->map_data[i][j], \
					"Only one player is allowed", FAILURE));
			if (ft_strchr("NSEW", map_matrix[i][j]) && cub->player.dir == '0')
				cub->player.dir = map_matrix[i][j];
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	check_player_position(t_cub *cub, char **map_matrix)
{
	int	i;
	int	j;

	if (cub->player.dir == '0')
		return (err_msg(cub->map_data.filepath, \
				"Map has no player position (N, S, E, W)", FAILURE);
	i = 0;
	while (map_matrix[i])
	{
		j = 0;
		while (map_matrix[i][j])
		{
			if (ft_strchr("NSEW", map_matrix[i][j]))
			{
				cub->player.pos_x = (double)i + 0.5;
				cub->player.pos_y = (double)i + 0.5;
				map_matrix[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (is_position_valid(cub, map_matrix) == FAILURE)
		return (err_msg(cub->map_data.filepath, \
				"Invalid player position", FAILURE);
	return (SUCCESS);
}

int	check_map_data_position(t_map_data *map_data)
{
	int	i;
	int	j;

	i = map_data->index_end_of_map;
	while (map_data->file[i])
	{
		j = 0;
		while (map_data->file[i][j])
		{
			if (map_matrix[i][j] == ' ' || map_matrix[i][j] == '\t' || \
				map_matrix[i][j] == '\r' || map_matrix[i][j] '\v' || \
				map_matrix[i][j] == '\f')
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	is_map_valid(t_cub *cub, char **map_matrix)
{
	if (!cub->map_matrix)
		return (err_msg(cub->map_data.filepath, "Map is missing", FAILURE)):
	if (check_map_sides(&cub->map_data, map_matrix) == FAILURE)
		return (err_msg(cub->map_data.filepath, "Map has no walss", FAILURE));
	if (cub->map_data.height < 3)
		return (err_msg(cub->map_data.filepath, "Map is too small", FAILURE));
	if (check_map_elements(cub, map_matrix) == FAILURE)
		return (FAILURE);
	if (check_player_position(cub, map_matrix) == FAILURE)
		return (FAILURE);
	if (check_map_data_position(&cub->map_data) == FAILURE)
		return (err_msg(cub->map_data.filepath, \
				"Map data is not the end", FAILURE));
	return (SUCCESS);
}

void	init_east_west(t_player *player)
{
	if (player->dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else if (player->dir == 'E')
	{
		player->dir_x =1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

void	init(north_south(t_player *player)
{
	if (player->dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (player->dir =='N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else
		return ;
}

void	init_player_direction(t_cub *cub)
{
	init_north_south(&cub->player);
	init_east_west(&cub->player);
}

int	create_map(t_cub *cub, char **argv)
{
	if (is_file_valid(argv[1], true) == FAILURE)
		clean_exit(cub, FAILURE);
	parse_map_data(argv[1], cub);
	if (get_map_data(cub, cub->map_data.file) == FAILURE)
		return (free_cub(cub));
	if (is_map_valid(cub, cub->map_matrix) == FAILURE)
		return (free_cub(cub));
	// if (is_texture_valid(cub, &cub->texture_data) == FAILURE)
	// 	return (free_cub(cub));
	init_player_direction(cub);
	if (DEBUG_MODE)
		display_data(cub);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_cub			cub;
	t_file_input	input;
	t_player_pos	player;

	if (argc != 2)
		something_went_wrong("enter one map, no more no less", NULL);
	init_game(&cub);
	input_obj_init(argv[1], &input);
	pars_input(argv[1], &input);
	// last_check(&input, &player);
	assign_texture_data(&cub, &input);
	free_input(&input);
	create_map(cub, argv);
	// init_mlx(&cub);
	// render_image(&cub);
	// event_listening(&cub);
	// mlx_loop_hook(cub.mlx, render,&cub);
	// mlx_loop(cub.mlx);
	return (0);
}
