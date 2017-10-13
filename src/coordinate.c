#include <math.h>
#include <stdio.h>
#include "coordinate.h"

/* Return the squared distance between a point and the origin
** [in]  point to measure
*/
static int dist2(point_t point)
{
    return(point.x * point.x + point.y * point.y);
}

void resize_coordinates(path_t * path, int diameter)
{
    // C is a circle which contain all points of 'path'
    // Get center (c) of C
    point_t c = {0, 0};
    for(int i = 0; i < path->nb_points; i++) {
        c.x += path->points[i].x;
        c.y += path->points[i].y;
    }
    c.x /= path->nb_points;
    c.y /= path->nb_points;
    // Move all point to have (0,0) as center
    for(int i = 0; i < path->nb_points; i++) {
        path->points[i].x -= c.x;
        path->points[i].y -= c.y;
    }
    // Get min radius (r) of C
    int r = dist2(path->points[0]);
    int dist;
    for(int i = 1; i < path->nb_points; i++)
        if((dist = dist2(path->points[i])) < r)
            r = dist;
    // Scale points to fit them into C
    float ratio = diameter / 2.0 / sqrt(r);
    for(int i = 0; i < path->nb_points; i++) {
        path->points[i].x *= ratio;
        path->points[i].y *= ratio;
    }
}

point_t xy2rt(point_t point)
{
    point_t p = {
        sqrt(point.x * point.x + point.y * point.y),
        atan2(point.y, point.x)
    };
    return p;
}
