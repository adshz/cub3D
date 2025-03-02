#include"cub3d.h"

void something_went_wrong(char *str, t_file_input *input)
{
    if(input)
        free_input(input);
    printf("%s\n",str);
    exit(EXIT_FAILURE);
}

bool str_cmp(char *s1, char *s2, int k)
{
    int i;

    i = 0;
    while(k > i)
    {
         if (s1[i] == s2[i])
            ++i;
        else
            return (false);
    }
    return (true);
}