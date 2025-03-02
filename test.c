#include "cub3d.h"

/*
bool	flood_fill(int **map, int start_x, int start_y, int size)
{
	int	d;
	int	front;
	int	rear;
	int	new_x;
	int	new_y;

	int	directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	t_point *queue = malloc(size * size * sizeof(t_point));
	if (!queue)
		return (false);
	front =  rear = 0;
	queue[rear++] = (t_point){start_x, start_y};
	map[start_x][start_y] = 38;
	while (front < rear)
	{
		t_point current = queue[front++];
		d = 0;
		while(d < 4)
		{
			new_x = current.x + directions[d][0];
			new_y = current.y + directions[d][1];
			if ((new_x < 1 || new_y < 1 || new_x > size || new_y > size)
					|| (map[new_x][new_y] == 21))
			{
				free(queue);
				return (false);
			}
			if (map[new_x][new_y] == 0)
			{
				map[new_x][new_y] = 38;
				queue[rear++] = (t_point){new_x, new_y};
			}
			++d;
		}
	}
	free(queue);
	return (true);
}
*/
bool	flood_fill(int **map, int x, int y, int size)
{
	t_point		*queue;
	t_point		curr;
	int			front;
	int			rear;
	int			d;

	queue = malloc(size * size * sizeof(t_point));
	if (!queue)
		return (false);
	front = 0;
	rear = 0;
	queue[rear++] = (t_point){x, y};
	map[x][y] = 38;
	while (front < rear)
	{
		curr = queue[front++];
		d = -1;
		while (++d < 4)
		{
			x = curr.x + (d == 0) - (d == 1);
			y = curr.y + (d == 2) - (d == 3);
			if (x < 1 || y < 1 || x >= size || y >= size || map[x][y] == 21)
			{
				free(queue);
				return (false);
			}
			if (map[x][y] == 0)
			{
				map[x][y] = 38;
				queue[rear++] = (t_point){x, y};
			}
		}
	}
	free(queue);
	return (true);
}