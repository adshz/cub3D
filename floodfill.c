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
typedef struct s_point
{
    int x;
    int y;
} t_point;


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

bool flood_fill(int **map, int start_x, int start_y, int size)
{
    int d;
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Down, Up, Right, Left

    t_point *queue = malloc(size * size * sizeof(t_point)); // Allocate space for the queue
    if (!queue)
        return false; // Memory allocation failure

    int front = 0, rear = 0;

    queue[rear++] = (t_point){start_x, start_y}; // Push starting point into the queue
    map[start_x][start_y] = 38; // Mark as visited

    while (front < rear) // While queue is not empty
    {
        t_point current = queue[front++]; // Dequeue
        d = 0;
        while(d < 4)
        {
            int new_x = current.x + directions[d][0];
            int new_y = current.y + directions[d][1];

            if ((new_x < 1 || new_y < 1 || new_x > size || new_y > size)
                || (map[new_x][new_y] == 21))
            {
                free(queue);
                return false; // Found an opening in the map => Not enclosed
            }
            if (map[new_x][new_y] == 0) // Unvisited open space
            {
                map[new_x][new_y] = 38; // Mark as visited
                queue[rear++] = (t_point){new_x, new_y}; // Enqueue
            }
            ++d;
        }
    }
    free(queue);
    print_map(map,size);
    return true; // Successfully filled area without hitting an opening
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