/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:39:42 by aalissa           #+#    #+#             */
/*   Updated: 2025/05/09 17:11:38 by szhong           ###   ########.fr       */
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


int	create_map(t_cub *cub, char **argv)
{
	if (is_file_valid(argv[1], true) == FAILURE)
		clean_exit(cub, FAILURE);
	parse_map_data(argv[1], cub);
	if (get_map_data(cub, cub->map_data.file) == FAILURE)
		return (free_cub(cub));
	if (is_map_valid(cub, cub->map_matrix) == FAILURE)
		return (free_cub(cub));
	if (is_texture_valid(cub, &cub->texture_data) == FAILURE)
		return (free_cub(cub));
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
	last_check(&input, &player);
	assign_texture_data(&cub, &input);
	print_input(&input);
	free_input(&input);
	return (0);
}
