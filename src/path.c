#include "path.h"
#include <stdio.h>

void display_path(path_t* path)
{
    for(int i = 0; i < path->nb_points; i++)
        printf("\t[%f, %f]\n", path->points[i].x, path->points[i].y);
}
