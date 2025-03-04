#include "cub3d.h"

void	copy_map(int **src, int ***dest, int size)
{
	int	i;
	int	j;

	*dest = malloc(sizeof(int *) * size);
	if (!*dest)
		something_went_wrong("Memory allocation failed!", NULL);
	i = 0;
	while (i < size)
	{
		(*dest)[i] = malloc(sizeof(int) * size);
		if (!(*dest)[i])
			something_went_wrong("Memory allocation failed!", NULL);
		j = 0;
		while (j < size)
		{
			(*dest)[i][j] = src[i][j];
			j++;
		}
		i++;
	}
}

void	free_map(int **map, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static bool	process_queue_item(t_flood_fill_data *data, t_point curr)
{
	int	d;
	int	x;
	int	y;

	d = -1;
	while (++d < 4)
	{
		x = curr.x + (d == 0) - (d == 1);
		y = curr.y + (d == 2) - (d == 3);
		if (x < 1 || y < 1 || x >= data->size || y >= data->size || \
				data->map[x][y] == 21 || data->map[x][y] == -16)
		{
			free(data->queue);
			return (false);
		}
		if (data->map[x][y] == 0)
		{
			data->map[x][y] = 38;
			data->queue[(*data->rear)++] = (t_point){x, y};
		}
	}
	(*data->front)++;
	return (true);
}

bool	flood_fill(int **map, int y, int x, int size)
{
	t_point				*queue;
	t_point				curr;
	t_flood_fill_data	data;
	int					front;
	int					rear;

	queue = malloc(size * size * sizeof(t_point));
	if (!queue)
		return (false);
	front = 0;
	rear = 0;
	queue[rear++] = (t_point){x, y};
	map[x][y] = 38;
	data.map = map;
	data.queue = queue;
	data.front = &front;
	data.rear = &rear;
	data.size = size;
	while (front < rear)
	{
		curr = queue[front];
		if (!process_queue_item(&data, curr))
			return (false);
	}
	free(queue);
	return (true);
}

bool	check_map_enclosed(t_file_input *input, int y, int x)
{
	bool	valid;
	int		**map_copy;

	valid = false;
	copy_map(input->map, &map_copy, input->map_size);
	valid = flood_fill(map_copy, y, x, input->map_size);
	free_map(map_copy, input->map_size);
	return (valid);
}

void	last_check(t_file_input *input, t_player_pos *player)
{
	int	i;
	int	j;
	int	size;
	int	flag;	

	size = input->map_size;
	flag = 0;
	i = -1;
	while (++i < size)
	{
		j = 0;
		while (++j < size)
		{
			if (input->map[i][j] == -42)
				something_went_wrong("Invalid map character!", input);
			if (input->map[i][j] == -2)
			{
				++flag;
				player_pos_init(player, j, i);
				if (flag > 1 || !check_map_enclosed(input, j, i))
					something_went_wrong("Map is not enclosed!", input);
			}
		}
	}
}
