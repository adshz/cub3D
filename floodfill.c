#include "cub3d.h"

void copy_map(int **src, int ***dest, int size)
{
    int i, j;

    *dest = malloc(sizeof(int *) * size);
    if (!*dest)
        something_went_wrong("Memory allocation failed!");

    i = 0;
    while (i < size)
    {
        (*dest)[i] = malloc(sizeof(int) * size);
        if (!(*dest)[i])
            something_went_wrong("Memory allocation failed!");
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

bool flood_fill(int **map, int i, int j, int size)
{
    if (i < 0 || j < 0 || i >= size || j >= size)
        return false; // Reached boundary => map is open

    if (map[i][j] == 1 || map[i][j] == -1)
        return true; // Hit a wall or already visited area

    if (map[i][j] == 0)
        map[i][j] = -1; // Mark as visited

    if (!flood_fill(map, i + 1, j, size)) return false; // Down
    if (!flood_fill(map, i - 1, j, size)) return false; // Up
    if (!flood_fill(map, i, j + 1, size)) return false; // Right
    if (!flood_fill(map, i, j - 1, size)) return false; // Left

    return true;
}



bool check_map_enclosed(t_file_input *input, int x, int y)
{
    int **map_copy;
    copy_map(input->map, &map_copy, input->map_size);

    bool valid = flood_fill(map_copy, y, x, input->map_size);

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
            {
                free_input(input);
                something_went_wrong("Invalid map character!");
            }
            if (input->map[i][j] == -2)
            {
                ++flag;
                player_pos_init(player, j, i);
                if (flag != 1 || !check_map_enclosed(input, i, j))
                {
                    free_input(input);
                    something_went_wrong("Map is not enclosed!");
                }
            }
        }
    }
}