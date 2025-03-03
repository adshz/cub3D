#include"cub3d.h"

void	border_setup(t_file_input *input)
{
	int	i;
	int	j;
	int	map_size;

	map_size = input->map_size;
	j = -1;
	while (++j < map_size)
	{
		input->map[0][j] = 42;
		input->map[map_size - 1][j] = 42;
	}
	i = -1;
	while (++i < map_size)
	{
		input->map[i][0] = 42;
		input->map[i][map_size - 1] = 42;
	}
}

void	map_obj_init(t_file_input	*input)
{
	int	i;
	int	j;
	int	map_size;

	map_size = input->map_size;
	i = -1;
	input->map = malloc(sizeof(int *) * (map_size + 1));
	if (!input->map)
		something_went_wrong("Memory allocation failed for map rows!", NULL);
	while (++i < map_size)
	{
		input->map[i] = malloc(sizeof(int) * map_size);
		if (!input->map[i])
			something_went_wrong("Memory allocation failed for map row!", NULL);
		j = -1;
		while (++j < map_size)
			input->map[i][j] = 21;
	}
	input->map[map_size] = NULL;
	border_setup(input);
}

void	malloc_obj(t_file_input *input)
{
	int	j;

	j = 0;
	input->textures_path = malloc(sizeof(char *) * 7);
	if (!input->textures_path)
		something_went_wrong("Memory allocation failed for textures path!", \
				NULL);
	while (j < 6)
	{
		input->textures_path[j] = NULL;
		++j;
	}
	input->textures_path[6] = NULL;
	map_obj_init(input);
}

void	input_obj_init(char *file, t_file_input *input)
{
	int		j;
	int		i;
	int		fd;
	char	*line;

	i = 0;
	j = 0;
	line = NULL;
	if (!check_extension(file))
		something_went_wrong("Wrong file extension!", NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		something_went_wrong("File doesn't exist! Stop trolling, please.", \
				NULL);
	while ((line = get_next_line(fd)))
	{
		if ((int)ft_strlen(line) > j)
			j = (int)ft_strlen(line);
		++i;
		free(line);
	}
	close(fd);
	if (i < 9)
		something_went_wrong("wrong file format", NULL);
	if (i - 6 > j)
		input->map_size = i - 4;
	input->map_size = j + 2;
	input->textures_counter = 0;
	malloc_obj(input);
}

void	free_input(t_file_input *input)
{
	int	i;

	if (!input)
		return ;
	if (input->textures_path)
	{
		i = -1;
		while (input->textures_path[++i])
			free(input->textures_path[i]);
		free(input->textures_path);
		input->textures_path = NULL;
	}
	if (input->map)
	{
		i = -1;
		while (++i < input->map_size)
			free(input->map[i]);
		free(input->map);
		input->map = NULL;
	}
}
