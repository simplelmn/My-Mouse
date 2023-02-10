#include <stdio.h>
#include <stdlib.h>
#include "include/my_mouse.h"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        perror("Enter map");
        exit(EXIT_FAILURE);
    }
    else
    {
        if (my_mouse(argv[1]) == -1)
        {
            fprintf(stderr,"MAP ERROR");
            return 1;
        }
    }
    return 0;
}