#include <stdio.h>
#include "path.h"

void display_path(path_t * path)
{
    for(int i = 0; i < path->nb_points; i++)
        printf("[%f, %f]\n", path->points[i].x, path->points[i].y);
}
