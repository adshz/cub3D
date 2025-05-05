/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalissa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:39:42 by aalissa           #+#    #+#             */
/*   Updated: 2025/03/07 17:39:53 by aalissa          ###   ########.fr       */
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
	char	*path;
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
	int				ceiling;
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
}	t_cub;

void	init_map_data(t_map_data *map_data)
{
	map_data->fd = 0;
	map_data->line_count = 0;
	map_data->path = NULL;
	map_data->file = NULL;
	map_data->height = 0;
	map_data->width = 0;
	map_data->index_end_of_map = 0;
}

void	init_player(t_player *player)
{
	printf("%s here player %p\n", __func__, player);
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
	printf("%s here texture_data %p\n", __func__, texture_data);
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
	printf("%s yeah the pointer of cub is %p\n", __func__, cub);
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->win_height = WIN_HEIGHT;
	cub->win_width = WIN_WIDTH;
	init_player(&cub->player);
	init_texture_data(&cub->texture_data);
	cub->map_matrix = NULL;
	init_map_data(&cub->map_data);
	init_mlx_img(&cub->mlx_img);

	return ;
}
void	init_game(t_cub *cub)
{
	printf("%s yeah the pointer of cub is %p\n", __func__, cub);
	init_data(cub);
	return ;
}

char	*get_texture_path(char *line, int i)
{
	// #TODO
	// I don't think we need this complex because the parse is done already
	// so next step
	// I will simply print the `t_file_input input->textures_path` to see if it
	// is clear
	// =====================================
	// int		len;
	// int		j;
	// char	*path;
	// while (line[i] && (line[i] == ' ' || line[i] == '\t')
	// 	i++;
	// len = i;
	// while (line[len] && (line[len] != ' ' && line[len] != '\t'))
	// 	len++;
	// path = malloc(sizeof(char) * (len - i + 1);
	// if (!path)
	// 	return (NULL);
	// j = 0;
	// while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'))
	// 	path[j++] = line[i++];
	// path[j] = '\0';
	// while (line[i] && (line[i] == ' ' || line[i] == '\t'))
	// 	i++;
	// if (line[i] && line[i] != '\n')
	// {
	// 	free(path);
	// 	path = NULL;
	// }
	// return (path);
}

int	get_dir_texture_data(t_texture_data *texture, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' && line[i + 1] == 'O' && !(texture->north))
			texture->north = get_texture_path(line, i + 2);
	}
	

}
void	assign_map_data(t_cub *cub, t_file_input *map_file)
{
	int	i;
	int	j;

	i = -1;
	while (map_file->textures_path[++i])
		get_dir_texture_data(t_texture_data *texture, map_file->texttures_path[i]);
}
int	main(int c, char **v)
{
	t_cub			cub;
	t_file_input	input;
	t_player_pos	player;

	if (c != 2)
		something_went_wrong("enter one map, no more no less", NULL);
	init_game(&cub);
	input_obj_init(v[1], &input);
	pars_input(v[1], &input);
	last_check(&input, &player);
	assign_map_data(&cub, &input);
	print_input(&input);
	free_input(&input);
	return (0);
}
