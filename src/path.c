#include "path.h"
#include <stdio.h>
#include "coordinate.h"
#include "conf.h"

void display_path(path_t* path)
{
    for(int i = 0; i < path->nb_points; i++)
        printf("\t[%f, %f]\n", path->points[i].x, path->points[i].y);
}

int find_when_stop_pump(path_t * path)
{
    float all_dist = 0;
    for(int i = 1; i < path->nb_points; i++)
        all_dist += dist(path->points[i-1], path->points[i]);
    if(all_dist <= PUMP_STOP_DIST)
        return 0;
    return(all_dist - PUMP_STOP_DIST);
}
