#include"cub3d.h"

int main(int c, char **v)
{
    t_file_input input;
    t_player_pos player;

    if (c != 2)
        somthing_went_wrong("enter one map, no more no less");
    obj_init(v[1], &input);
    pars_input(v[1], &input);
    last_check(&input, &player);
//    print_input(&input);
    free_input(&input);
    return (0);
}