#include"cub3d.h"

bool valid_start_point(char c)
{
    if(c == 'N' || c == 'S'
        || c == 'W' || c == 'E')
        return true;
    return false;
}

bool valid_char(char c)
{
    if (is_blank(c) || c == '0' || c == '1' ||(valid_start_point(c)))
        return true;
    return false;
}

int check_map_data_type(char c, t_file_input * input)
{
    if(!valid_char(c))
        return (-42);
    else if (valid_start_point(c))
    {
        input->palyer_spawn_direction = c;
        return (-2);
    }
    return (c - '0');
}

bool    check_extension(char *str)
{
    while(*str)
        ++str;
    str = str - 4;
    if (str_cmp(str,".cub",4))
        return (true);
    return (false);
}

void texture_assignment(char *line, t_file_input *input)
{
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < 6 && input->textures_path[i] != NULL)
        i++;
    
    if (i >= 6)
        something_went_wrong("Too many textures!", NULL);
    while (line[k] && is_blank(line[k]))
        k++;
    size_t len = ft_strlen(line + k);
    input->textures_path[i] = malloc(sizeof(char) * (len + 1));
    if (!input->textures_path[i])
        something_went_wrong("Memory allocation failed!", NULL);
    while (line[k])
        input->textures_path[i][j++] = line[k++];
    input->textures_path[i][j] = '\0'; // Null-terminate the string
//    printf("proccesed line %s\n", input->textures_path[i]);
}

void map_assigment(char *line, t_file_input *input)
{
    int i = 0, j = 0;
    int map_size = input->map_size;

    if (!input || !input->map) // Ensure valid input
        return;
    while (i < map_size && input->map[i] && input->map[i][1] != 21)
        ++i;
    
    if (i >= map_size || !input->map[i])
        return;
    
    j = 0;
    while (line[j] && j < map_size - 2)
    {
        input->map[i][j + 1] = check_map_data_type(line[j], input);
        ++j;
    }
    while (j < map_size - 1)
    {
        input->map[i][j + 1] = 21;
        ++j;
    }
}

void    line_assigment(char *line, t_file_input* input)
{
    if(str_cmp(line,"NO",2) || str_cmp(line,"SO",2)
    || str_cmp(line,"WE",2) || str_cmp(line,"EA",2)
    || str_cmp(line,"F",1) || str_cmp(line,"C",1))
    {
        printf("assigining line %s\n", line);
        input->textures_counter += 1;
        texture_assignment(line, input);
    }
    else
        map_assigment(line, input);
}

void player_pos_init(t_player_pos *player, int x_pos, int y_pos)
{
    player->player_x_pox = x_pos;
    player->player_y_pos = y_pos;
}

void    pars_input(char *file,t_file_input* input)
{
    int fd;
    char *line;

    line = NULL;
    fd = open(file,O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if(!line)
            break;
        line_assigment(line, input);
        free(line);
    }
    close(fd);
}