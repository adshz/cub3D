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

void texture_assigment(char *line, t_file_input *input)
{
    int i = 0;
    int k = 0;
    int j = 0;

    while (input->textures_path[i] != NULL && i < 6)
        ++i;
    if (i >= 6) {
        somthing_went_wrong("Too many textures!");
        return;
    }

    k = str_len(line);
    input->textures_path[i] = malloc(sizeof(char) * (k + 1));
    k = 0;
    while (line[k])
    {
        if (!is_blank(line[k]))
        {
            input->textures_path[i][j] = line[k];
            ++j;
        }
        ++k;
    }

    input->textures_path[i][j] = '\0';
}

void map_assigment(char *line, t_file_input *input)
{
    int i = 0, j = 0;
    int map_size = input->map_size;

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
        texture_assigment(line, input);
    else
        map_assigment(line,input);
}

void player_pos_init(t_player_pos *player, int x_pos, int y_pos)
{
    player->player_x_pox = x_pos;
    player->player_y_pos = y_pos;
}

void last_check(t_file_input* input, t_player_pos* player)
{
    int i = -1;
    int j;
    int size = input->map_size;
    while(++i < size)
    {
        j = -1;
        while (++j < size)
        {
            if (input->map[i][j] == -42)
            {
                free_input(input);
                somthing_went_wrong("wrong map char");
            }
            if (input->map[i][j] == -2)
                player_pos_init(player, j, i);
        }
    }
}

void    pars_input(char *file,t_file_input* input)
{
    int fd;
    char *line;

    line = NULL;
    if(!check_extension(file))
        somthing_went_wrong("wrong file extention!!");
    fd = open(file,O_RDONLY);
    if (-1 == fd)
        somthing_went_wrong("file doesn't exist!!\nstop trolling please");
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