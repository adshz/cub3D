/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:39:42 by aalissa           #+#    #+#             */
/*   Updated: 2025/06/20 16:26:10 by szhong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
#include <stdio.h>
#include <string.h>

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

void	init_game(t_cub *cub, t_file_input *input)
{
	init_data(cub);
	input_obj_init(argv[1], &input);
	return ;
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

	i = -1;
	while (map_file->textures_path[++i])
	{
		if (1 == get_direction_texture_data(&cub->texture_data, map_file->textures_path[i]))
			break ;
	}
}

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

int	is_file_valid(char *arg, bool is_cub)
{
	int	fd;

	if (is_dir(arg))
		return (err_msg(arg, "is a directory", FAILURE));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (err_msg(arg, strerror(errno), FAILURE));
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
		free_matrix((void **)cub->texture_pixels);
	free_texture_data(&cub->texture_data);
	free_map_data(cub);
	return (FAILURE);
}

void	clean_exit(t_cub *cub, int code)
{
	if (!cub)
		exit(code);
	if (cub->win_ptr && cub->mlx_ptr)
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
	if (cub->mlx_ptr)
	{
		mlx_destroy_display(cub->mlx_ptr);
		mlx_loop_end(cub->mlx_ptr);
		free(cub->mlx_ptr);
	}
	free_cub(cub);
	exit(code);
}


void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*dst;

	dst = s;
	while (n > 0)
	{
		*dst = (unsigned char) c;
		dst++;
		n--;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	total_size;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (size * nmemb > ((size_t)(-1)))
		return (NULL);
	if ((int)nmemb < 0 || (int)size < 0)
		return (NULL);
	total_size = nmemb * size;
	mem = malloc(total_size);
	if (mem == NULL)
		return (NULL);
	ft_memset(mem, 0, total_size);
	return (mem);
}

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
		err_msg(NULL, "Failed to allocate memory", FAILURE);
		return ;
	}
	cub->map_data.fd = open(filepath, O_RDONLY);
	if (cub->map_data.fd < 0)
		err_msg(filepath, strerror(errno), FAILURE);
	else
	{
		fill_matrix(row, col, i, cub);
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
			return (err_msg(NULL, ERR_MALLOC, FAILURE));
		while (map_data->file[index][j] && map_data->file[index][j] != '\n')
		{
			map_matrix[i][j] = map_data->file[index][j];
			j++;
		}
		while (j < map_data->width)
			map_matrix[i][j++] = '\0';
		i++;
		index++;
	}
	map_matrix[i] = NULL;
	return (SUCCESS);
}

int	count_map_lines(t_cub *cub, char **file, int i)
{
	int	start;
	int	j;

	start = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r' \
			|| file[i][j] == '\v' || file[i][j] == '\f')
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	cub->map_data.index_end_of_map = i;
	return (i - start);
}

int	get_map_info(t_cub *cub, char **file, int i)
{
	cub->map_data.height = count_map_lines(cub, file, i);
	cub->map_matrix = malloc(sizeof(char *) * (cub->map_data.height + 1));
	if (!cub->map_matrix)
		return (err_msg(NULL, ERR_MALLOC, FAILURE));
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
	if (ft_isdigit(map[i][j]))
	{
		if (assign_map_data(cub, map, i) == FAILURE)
			return (err_msg(cub->map_data.filepath, \
				"Please check if map description is wrong or incomplete", \
				FAILURE));
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
				return (SUCCESS);
			j ++;
		}
		i++;
	}
	return (ret);
}

int	check_top_or_bottom(char **map_matrix, int i, int j)
{
	if (!map_matrix || !map_matrix[i] || !map_matrix[i][j])
		return (FAILURE);
	while (map_matrix[i][j] == ' ' || map_matrix[i][j] == '\t' || \
		map_matrix[i][j] == '\r' || map_matrix[i][j] == '\v' || \
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
		j = (int)ft_strlen(map_matrix[i]) - 1;
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
				map_matrix[i][j] == '\r' || map_matrix[i][j] == '\v' || \
				map_matrix[i][j] == '\f')
				j++;
			if (!(ft_strchr("10NSEW", map_matrix[i][j])))
				return (err_msg(cub->map_data.filepath, \
					"Invalid character in map", FAILURE));
			if (ft_strchr("NSEW", map_matrix[i][j]) && cub->player.dir != '0')
				return (err_msg(cub->map_data.filepath, \
					"Only one player is allowed", FAILURE));
			if (ft_strchr("NSEW", map_matrix[i][j]) && cub->player.dir == '0')
				cub->player.dir = map_matrix[i][j];
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	is_whitespace(char c)
{
	if (c != ' ' && c != '\t' && c != '\r' && c != '\n' \
		&& c != '\v' && c != '\f')
		return (FAILURE);
	return (SUCCESS);
}

int	is_position_valid(t_cub *cub, char **map_matrix)
{
	int	i;
	int	j;

	i = (int)cub->player.pos_y;
	j = (int)cub->player.pos_x;
	if (ft_strlen(map_matrix[i - 1]) < (size_t)j || \
		ft_strlen(map_matrix[i + 1]) < (size_t)j || \
		is_whitespace(map_matrix[i][j - 1]) == SUCCESS || \
		is_whitespace(map_matrix[i][j + 1]) == SUCCESS || \
		is_whitespace(map_matrix[i - 1][j]) == SUCCESS || \
		is_whitespace(map_matrix[i + 1][j]) == SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int	check_player_position(t_cub *cub, char **map_matrix)
{
	int	i;
	int	j;

	if (cub->player.dir == '0')
		return (err_msg(cub->map_data.filepath, \
				"Map has no player position (N, S, E, W)", FAILURE));
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
				"Invalid player position", FAILURE));
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
			if (map_data->file[i][j] == ' ' || map_data->file[i][j] == '\t' || \
				map_data->file[i][j] == '\r' || map_data->file[i][j] == '\v' || \
				map_data->file[i][j] == '\f')
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
		return (err_msg(cub->map_data.filepath, "Map is missing", FAILURE));
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

void	init_north_south(t_player *player)
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
	init_player_direction(cub);
	if (DEBUG_MODE)
		display_data(cub);
	return (SUCCESS);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nbl;

	nbl = n;
	if (nbl == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (nbl < 0)
	{
		nbl *= -1;
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(nbl, fd);
	}
	else if (nbl > 9)
	{
		ft_putnbr_fd(nbl / 10, fd);
		ft_putnbr_fd(nbl % 10, fd);
	}
	else
		ft_putchar_fd(nbl + 48, fd);
}

int	is_rgb_valid(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (ft_putnbr_fd(rgb[i], 2), \
			err_msg(NULL, " is invalid RGB value", FAILURE));
		i++;
	}
	return (SUCCESS);
}

int	is_texture_valid(t_cub *cub, t_texture_data *textures)
{
	if (!textures->north || !textures->south || !textures->west \
		|| !textures->east)
		return (err_msg(cub->map_data.filepath, "Textures missing", FAILURE));
	if (!textures->floor || !textures->ceiling)
		return (err_msg(cub->map_data.filepath, "Colours missing", FAILURE));
	if (is_file_valid(textures->north, false) == FAILURE || \
		is_file_valid(textures->south, false) == FAILURE || \
		is_file_valid(textures->west, false) == FAILURE || \
		is_file_valid(textures->east, false) == FAILURE || \
		is_rgb_valid(textures->floor) == FAILURE || \
		is_rgb_valid(textures->ceiling) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

unsigned long	convert_rgb_to_hex(int *rgb_matrix)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb_matrix[0];
	g = rgb_matrix[1];
	b = rgb_matrix[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

void parse_file(char **argv, t_cub *cub, t_file_input *input)
{
	if (is_file_valid(argv[1], true) == FAILURE)
		clean_exit(cub, FAILURE);
	parse_map_data(argv[1], cub);
	pars_input(argv[1], &input);
}

void  assign_data(t_cub *cub, t_file_input *input)
{
	assign_texture_data(&cub, &input);
  free(input);
	if (get_map_data(cub, cub->map_data.file) == FAILURE)
		return (free_cub(cub));
}

int validate_data(t_cub *cub)
{
	if (is_map_valid(cub, cub->map_matrix) == FAILURE)
		return (free_cub(cub));
	if (is_texture_valid(&cub, &cub.texture_data) == FAILURE)
		return (free_cub(&cub));
	cub.texture_data.hex_floor = convert_rgb_to_hex(cub.texture_data.floor);
	cub.texture_data.hex_ceiling = convert_rgb_to_hex(cub.texture_data.ceiling);
	init_player_direction(cub);
	if (DEBUG_MODE)
		display_data(cub);
  return (SUCCESS);
}

void  init_mlx(t_cub *cub)
{
  cub->mlx_ptr = mlx_init();
  if (!cub->mlx)
    clean_exit(cub, err_msg("mlx", "Fail to start mlx", FAILURE));
  cub->win_ptr = mlx_new_window(cub->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "42Cub3D");
  if (!cub->win)
    clean_exit(cub, err_msg("mlx", "Fail to create a mlx window", FAILURE));
	if (BONUS)
		mlx_mouse_move(cub->mlx_ptr, cub->win_ptr, cub->win_width / 2,
			cub->win_height / 2);
  return ;
}

int *xpm_to_img(t_cub *cub, char *path)
{
  t_img tmp;
  int   *buffer;
  int   y;
  int   x;

  init_texture_img(cub, &tmp, path);

}

void  transform_textures(t_cub *cub)
{
	cub->textures = ft_calloc(5, sizeof * cub->textures);
	if (!cub->textures)
		clean_exit(cub, err_msg(NULL, ERR_MALLOC, 1));
	cub->textures[NORTH] = xpm_to_img(cub, cub->texture_data.north);
	cub->textures[SOUTH] = xpm_to_img(cub, cub->texture_data.south);
	cub->textures[EAST] = xpm_to_img(cub, cub->texture_data.east);
	cub->textures[WEST] = xpm_to_img(cub, cub->texture_data.west);
}

void  init_texture_pixels(t_cub *cub)
{
  int i;

  if (cub->texture_pixels)
    free_matrix((void **)cub->texture_pixels);
  cub->texture_pixels = ft_calloc(cub->win_height + 1, sizeof(int **));
  if (!cub->texture_pixels)
    clean_exit(cub, err_msg(NULL, ERR_MALLOC, 1));
  i = 0;
  while (i < cub->win_height)
  {
    cub->texture_pixels[i] = ft_calloc(cub->win_width + 1, sizeof * cub->texture_pixels);
    if (!cub->texture_pixels[i])
      clean_exit(cub, err_msg(NULL, ERR_MALLOC, 1));
    i++;
  }
}

void  init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_x) * ray->deltadist_y;
	}
}

void	perform_dda(t_cub *cub, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25 || ray->map_x > 0.25 || ray->map_y > cub->map_data.height - 0.25 || ray->map_x > cub->map_data.width - 1.25);
			break ;
		else if (cub->map_matrix[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

void	calculate_line_height(t_ray *ray, t_cub *cub, t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist(ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(cub->win_height / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 1 + cub->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + cub->win_height / 2;
	if (ray->draw_end >= cub->win_height)
		ray->draw_end = ray->line_height / 2 + cub->win_height / 2;
	if (ray->draw_end >= cub->win_height)
		ray->draw_end = cub->win_height - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	assign_texture_index(t_cub *cub, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			cub->texture_data.index = WEST;
		else
			cub->textue_data.index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			cub->texture_data.index = SOUTH;
		else
			cub->texture_data.indx = NORTH;
	}
}
void	update_texture_pixels(t_cub *cub, t_texture_data *texture, t_ray *ray, int x)
{
	int	y;
	int	color;

	assign_texture_index(cub, ray);
	texture->x = (int)(ray->wall_x * texture->size);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1 && ray->dir_y > 0)) 
		texture->x = texture->size - texture->x - 1;
	texture->step = 1.0 * texture->size / ray->line_height;
	texture->pos = (ray->draw_start - cub->win_height / 2 + ray->line_height / 2) * texture->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		texture->y = (int)texture->pos  & (texture->size - 1);
		texture->pos += texture->step;
		color = cub->textures[texture->index][texture->size * texture->y + texture->x];
		if (texture->index == NORTH || texture->index == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			cub->texture_pixels[y][x] = color;
		y++;
	}
}

void  init_raycasting_data(int x, t_ray *ray, t_player *player)
{
  init_ray(ray);
  ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
  ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
  ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
  ray->map_x = (int)player->pos_x;
  ray->map_y = (int)player->pos_y;
  ray->deltadist_x = fabs(1 / ray->dir_x);
  ray->deltadis_y = fabs(1 / ray->dir_y);
}

int build_raycasting(t_player *player, t_cub *cub)
{
  t_ray ray;
  int   x;

  x = 0;
  ray = cub->ray;
  while (x < cub->win_width)
  {
    init_raycasting_data(x, &ray, player);
    set_dda(&ray, player);
    perform_dda(cub, &ray);
    calculate_line_height(&ray, cub, player);
    update_texture_pixels(cub, &cub->texture_data, &ray, x);
    x++;
  }
  return (SUCCESS);
}

void  init_img(t_cub *cub, t_img *img, int width, int height)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
  img->img = mlx_new_image(data->mlx, width, height);
  if (!img->img)
    clean_exit(cub, err_msg("mlx", "Failed to create minilibx image", 1));
  img->addr = (int *)mlx_get_data_addr(img->img, &img->pixel_bits, &img->size_line, &img->endian);
  return ;
}

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

void  set_frame_image_pixel(t_cub *cub, t_img *image, int x, int y)
{
  if (cub->texture_pixels[y][x] > 0)
    set_image_pixel(image, x, y, cub->texture_pixels[y][x]);
  else if (y < cub->win_height / 2)
    set_image_pixel(image, x, y, cub->texture_data.hex_ceiling);
  else if (y < cub->win_height - 1)
    set_image_pixel(image, x, y, cub->texture_data.hex_floor);
  return ;
}

void  render_frame(t_cub *cub)
{
  t_img image;
  int   x;
  int   y;

  image.img_ptr = NULL;
  init_img(cub, &image, cub->win_width, cub->win_height);
  y = 0;
  while (y < cub->win_height)
  {
    x = 0;
    while (x < cub->win_width)
    {
      set_frame_image_pixel(cub, &image, x, y);
      x++;
    }
    y++;
  }
  mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, image.img, 0, 0);
  mlx_destroy_image(cub->mlx_ptr, image.img);
}

void  render_raycast(t_cub *cub)
{
  init_texture_pixels(cub);
  init_ray(&cub->ray);
  build_raycasting(&cub->player, cub);
  render_frame(cub);
}

# define MINIMAP_PIXEL_SIZE 128
# define MINIMAP_VIEW_DIST 4
# define MINIMAP_COLOR_PLAYER 0x00FF00
# define MINIMAP_COLOR_WALL 0x808080
# define MINIMAP_COLOR_FLOOR 0xE6E6E6
# define MINIMAP_COLOR_SPACE 0x404040

int get_minimap_offset(t_minimap *minimap, int mapsize, int pos)
{
  if (pos > minimap->view_dist && mapsize - pos > minimap->view_dist + 1)
    return (pos - minimap->view_dist);
  if (pos > minimap->view_dist && mapsize - pos <= minimap->view_dist + 1)
    return (mapsize - minimap->size);
  return (0);
}

char  *add_minimap_line(t_cub *cub, t_minimap *minimap, int y)
{
  char  *line;
  int   x;

  line = ft_calloc(minimap->size + 1, sizeof * line);
  if (!line)
    return (NULL);
  x = 0;
  while (x < minimap->size && x < cub->map_data.width)
  {
		if (!is_valid_map_coord(y + minimap->offset_y, cub->map_data.height)
			|| !is_valid_map_coord(x + minimap->offset_x, cub->map_data.width))
			line[x] = '\0';
		else if ((int)cub->player.pos_x == (x + minimap->offset_x)
			&& (int)cub->player.pos_y == (y + minimap->offset_y))
			line[x] = 'P';
		else if (cub->map[y + minimap->offset_y][x + minimap->offset_x] == '1')
			line[x] = '1';
		else if (cub->map[y + minimap->offset_y][x + minimap->offset_x] == '0')
			line[x] = '0';
		else
			line[x] = '\0';
		x++;
  }
}

char  **generate_minimap(t_cub *cub, t_minimap *minimap)
{
  char  **minimap_tmp;
  int   y;

  minimap_tmp = ft_calloc(minimap->size, sizeof * minimap_tmp);
  if (!minimap_tmp)
    return (NULL);
  y = 0;
  while (y < minimap->size && y < cub->map_data.height)
  {
    minimap_tmp[y] = add_minimap_line(cub, minimap, y);
    if (!minimap_tmp[y])
    {
      free_matrix((void **)minimap_tmp);
      return (NULL);
    }
    y++;
  }
  return (minimap_tmp);
}


void	render_minimap_image(t_cub *cub, t_minimap *minimap)
{
	int	img_size;

	img_size = MINIMAP_PIXEL_SIZE + minimap->tile_size;
	init_img(cub, &cub->minimap, img_size, img_size);
	draw_minimap(minimap);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->minimap.img,
		minimap->tile_size, cub->win_height
		- (MINIMAP_PIXEL_SIZE + (minimap->tile_size * 2)));
	mlx_destroy_image(cub->mlx_ptr, cub->minimap.img);
}

void  render_minimap(t_cub *cub)
{
  t_minimap minimap;

  minimap.map = NULL;
  minimap.img = &cub->minimap;
  minimap.view_dist = MINIMAP_VIEW_DIST;
  minimap.size (2 * minimap.view_dist) + 1;
  minimap.tile_size = get_minimap_offset(&minimap, cub->map_data.width, (int)cub->player.pos_x);
  minimap.offset_y = get_minimap_offset(&minimap, cub->map_data.height, (int)cub->player.pos_y);
  minimap.map = generate_minimap(cub, &minimap);
  if (!minimap.map)
  {
    err_msg(NULL, ERR_MALLOC, 0);
    return ;
  }
  if (MINIMAP_DEBUG_MSG)
    debug_display_minimap(&minimap);
  render_minimap_image(cub, &minimap);
  free_matrix((void **)minimap.map);
}

void  render_game(t_cub *cub)
{
  render_raycast(cub);
  if (BONUS)
    render_minimap(cub);
}

void	event_listening(t_cub *cub)
{
	mlx_hook(cub->win, ClientMessage, NoEventMask, quit_cub3d, cub);
	mlx_hook(cub->win, KeyPress, KeyPressMask, key_press_handler, cub);
	mlx_hook(cub->win, KeyRelease, KeyReleaseMask, key_release_handler, cub);
	if (BONUS)
		mlx_hook(cub->win, MotionNotify, PointerMotionMask,
			mouse_motion_handler, cub);
}

int	render_wrapper(t_cub *cub)
{
	cub->player.has_moved += move_player(cub);
	if (cub->player.has_moved == 0)
		return (0);
	render_game(cub);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub			cub;
	t_file_input	input;

	if (argc != 2)
		something_went_wrong("enter one map, no more no less", NULL);
	init_game(&cub &input);
	parse_file(argv[1], &cub, &input);
	assign_data(&cub, &input);
	if (validate_data(&cub) != SUCCESS)
		return (FAILURE);
	init_mlx(&cub);
	transform_textures(&cub)
	render_game(&cub);
	event_listening(&cub);
	mlx_loop_hook(cub.mlx_ptr, render_wrapper,&cub);
	mlx_loop(cub.mlx_ptr);
	return (0);
}
