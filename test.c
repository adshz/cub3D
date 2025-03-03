#include "cub3d.h"

void print_input(t_file_input *input)
{
    int i, j;

    if (!input)
    {
        printf("Input is NULL!\n");
        return;
    }

    // Print Textures
    printf("Textures Paths:\n");
    for (i = 0; input->textures_path[i] != NULL; i++)
    {
        printf("  [%d]: %s\n", i, input->textures_path[i]);
    }

    // Print Map
    printf("\nMap:\n");
    for (i = 0; input->map[i] != NULL; i++)
    {
        printf("Row: ");
        for (j = 0; j < input->map_size; j++)
        {
            printf("%d ", input->map[i][j]);
        }
        printf("\n");
    }
}