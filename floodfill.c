#include "cub3d.h"

void copy_map(int **src, int ***dest, int size)
{
    int i, j;

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


void free_map(int **map, int size)
{
    int i = 0;
    while (i < size)
    {
        free(map[i]);
        i++;
    }
    free(map);
}
/*
bool flood_fill(int **map, int i, int j, int size)
{
    if (i < 1 || j < 1 || i > size || j > size)
        return false; // Reached boundary => map is open

    if (map[i][j] == 1 || map[i][j] == 38 )
        return true; // Hit a wall or already visited area

    if (map[i][j] == 0)
        map[i][j] = 38; // Mark as visited

    if (!flood_fill(map, i + 1, j, size)) return false; // Down
    if (!flood_fill(map, i - 1, j, size)) return false; // Up
    if (!flood_fill(map, i, j + 1, size)) return false; // Right
    if (!flood_fill(map, i, j - 1, size)) return false; // Left

    return true;
}
*/

void print_map(int **map, int size)
{
    int i = 0;
    int j;
    while (i < size)
    {
        j = 0;
        while(++j < size)
            printf("%d  ",map[i][j]);
        printf("\n");
        i++;
    }
}

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
			if (x < 1 || y < 1 || x >= size || y >= size || map[x][y] == 21 || map[x][y] == -16)
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
    print_map(map,size);
	return (true);
}
bool check_map_enclosed(t_file_input *input, int y, int x)
{
    int **map_copy;
    copy_map(input->map, &map_copy, input->map_size);

    bool valid = flood_fill(map_copy, y, x,input->map_size);

    free_map(map_copy, input->map_size);

    return valid;
}

void last_check(t_file_input *input, t_player_pos *player)
{
    int i = 0, j, size = input->map_size, flag = 0;

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
                if (flag > 1 || !check_map_enclosed(input, i, j))
                    something_went_wrong("Map is not enclosed!", input);
            }
        }
    }
}