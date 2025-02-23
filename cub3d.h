#ifndef CUB3D_H
#define CUB3D_H

#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "get_next_line.h"
#include "minilibx-linux/mlx.h"
#include <time.h>

typedef struct s_file_input
{
    char **textures_path;
    int **map;
    int map_size;
}   t_file_input;


void print_input(t_file_input *input);
bool    check_extension(char *str);
void    obj_init(char * file,t_file_input *input);
void    pars_input(char *v,t_file_input* input);
bool    str_cmp(char *s1, char *s2, int k);
void    texture_assigment(char *line,t_file_input* input);
void    map_assigment(char *line,t_file_input* input);

void    somthing_went_wrong(char *str);

void    free_input(t_file_input* input);
#endif