#include "cub3d.h"

void	print_input(t_file_input *input)
{
	int	i;
	int	j;

	if (!input)
	{
		printf("Input is NULL!\n");
		return ;
	}
	printf("Textures Paths:\n");
	i = -1;
	while (input->textures_path[++i])
		printf("  [%d]: %s\n", i, input->textures_path[i]);
	printf("\nMap:\n");
	i = -1;
	while (input->map[++i])
	{
		printf("Row: ");
		j = -1;
		while (++j < input->map_size)
			printf("%d ", input->map[i][j]);
		printf("\n");
	}
}

void	print_map(int **map, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			printf("%d  ", map[i][j]);
		printf("\n");
	}
}
