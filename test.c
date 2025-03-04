#include "cub3d.h"

void	print_input(t_file_input *input)
{
	int	i;
	int	j;

	j = 0;
	if (!input)
	{
		printf("Input is NULL!\n");
		return ;
	}
	printf("Textures Paths:\n");
	while (input->texturs_path[++i])
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
