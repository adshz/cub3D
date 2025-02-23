#include"cub3d.h"

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

    // Find the next available row that is not initialized
    while (i < map_size && input->map[i] && input->map[i][1] != 21)
        ++i;
    
    if (i >= map_size || !input->map[i])  // Prevent accessing uninitialized rows
        return;
    
    j = 0;
    while (line[j] && j < map_size - 2) // Fill in the content (excluding borders)
    {
        input->map[i][j + 1] = line[j];  // Offset by 1 to keep border intact
        ++j;
    }

    // Fill remaining spaces with 42
    while (j < map_size - 1)
    {
        input->map[i][j + 1] = 21;
        ++j;
    }
}


/*
void    map_assigment(char *line, t_file_input *input)
{
    int i = 0;
    int j = 0;
    int map_size = input->map_size;

    while ((input->map[i]) && (input->map[i][1] != 42))
        ++i;
    while (line[j] && j < map_size)
    {
        input->map[i][j + 1] = line[j];
        ++j;
    }
    while (j < map_size)
    {
        input->map[i][j] = 42;
        ++j;
    }
}

*/
void    line_assigment(char *line, t_file_input* input)
{
    if(str_cmp(line,"NO",2) || str_cmp(line,"SO",2)
    || str_cmp(line,"WE",2) || str_cmp(line,"EA",2)
    || str_cmp(line,"F",1) || str_cmp(line,"C",1))
        texture_assigment(line, input);
    else
        map_assigment(line,input);
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