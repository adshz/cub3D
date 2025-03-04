#include "cub3d.h"

bool	valid_start_point(char c)
{
	if (c == 'N' || c == 'S'
		|| c == 'W' || c == 'E')
		return (true);
	return (false);
}

bool	valid_char(char c)
{
	if (is_blank(c) || c == '0' || c == '1' || (valid_start_point(c)))
		return (true);
	return (false);
}

int	check_map_data_type(char c, t_file_input *input)
{
	if (!(valid_char(c)))
		return (-42);
	else if (valid_start_point(c))
	{
		input->palyer_spawn_direction = c;
		return (-2);
	}
	return (c - '0');
}

bool	check_extension(char *str)
{
	while (*str)
		++str;
	str = str - 4;
	if (str_cmp(str, ".cub", 4))
		return (true);
	return (false);
}

void	line_check(char *line, int *max)
{
	int	counter;
	int	i;

	counter = 0;
	i = -1;
	while (line[++i])
	{
		if (valid_char(line[i]))
			++counter;
	}
	if (counter > *max)
		*max = counter;
}
