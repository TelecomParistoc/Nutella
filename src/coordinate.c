#include "coordinate.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "conf.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Offset of the motors positions
static point_t motor_offset;

/* Return the squared distance between a point and the origin
** [in]  point to compute
** [out] squared distance
*/
static inline int norm2(point_t point)
{
    return (point.x * point.x + point.y * point.y);
}

float dist(point_t p1, point_t p2)
{
    return (sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

/* Change coordinates from cartesian to polar
** [in]  point: cartesian coordinates
** [out] polar coordinates
*/
static point_t xy2rt(point_t point)
{
    point_t p = {
        sqrt(norm2(point)),
        atan2(point.y, point.x)};
    return p;
}

/* Move a set of points
** [in]  path: group of points to move
** [in]  offset: vector to move the points
*/
static void move_path(path_t* path, point_t* offset)
{
    for(int i = 0; i < path->nb_points; i++) {
        path->points[i].x += offset->x;
        path->points[i].y += offset->y;
    }
}

/* Rescale ans center a group of points to fit them in a circle
** [in]  path: group of points to resize
** [in]  diamter: diameter of the container circle
*/
static void resize_coordinates(path_t* path, int diameter)
{
    // C is a circle which contain all points of 'path'
    // Get opposite of the center (c) of C
    point_t c = {0, 0};
    for(int i = 0; i < path->nb_points; i++) {
        c.x += path->points[i].x;
        c.y += path->points[i].y;
    }
    c.x /= -path->nb_points;
    c.y /= -path->nb_points;
#ifdef DEBUG
    printf("\n[DEBUG][CENTER] Path center: [%f,%f]\n", c.x, c.y);
#endif
    // Move all point to have (0,0) as center
    move_path(path, &c);
    // Get min radius (r) of C
    int r = norm2(path->points[0]);
    int dist;
    for(int i = 1; i < path->nb_points; i++)
        if((dist = norm2(path->points[i])) > r)
            r = dist;
    // Scale points to fit them into C
    float ratio = diameter / 2.0 / sqrt(r);
    for(int i = 0; i < path->nb_points; i++) {
        path->points[i].x *= ratio;
        path->points[i].y *= ratio;
    }
}

/* Return the angles coordinates
** Usable by the Nutella printer
** [in]  point: point to compute
** [out] angles coordinates in rad
*/
static point_t xy2ab(point_t point)
{
    // Get coordinates as polar
    point_t angles = xy2rt(point);
    // Get angles of the motors to reach each points
    float b  = M_PI - 2 * acos(angles.x / 2.0 / DIST_L);
    angles.x = GEAR_RATIO * (angles.y + (M_PI - b) / 2);
    angles.y = b;
    return angles;
}

/* Get center of the path
** Center is calculated from motor angles
** [in]  path: points where center must be found
** [out] center coordinates in rad
*/
static point_t compute_motor_center(path_t* path)
{
    point_t angles = xy2ab(path->points[0]);
    float   min_a  = angles.x;
    float   max_a  = min_a;
    float   min_b  = angles.y;
    float   max_b  = min_b;
    for(int i = 0; i < path->nb_points; i++) {
        angles = xy2ab(path->points[i]);
        if(angles.x > max_a)
            max_a = angles.x;
        else if(angles.x < min_a)
            min_a = angles.x;
        if(angles.y > max_b)
            max_b = angles.y;
        else if(angles.y < min_b)
            min_b = angles.y;
    }
    angles.x = (min_a + max_a) / 2;
    angles.y = (min_b + max_b) / 2;
    return angles;
}

void compute_path(path_t* path, int diameter)
{
// Set center offset angles
#ifdef DEBUG
    printf("[DEBUG][PARSE] path after parsing:\n");
    display_path(path);
#endif
    resize_coordinates(path, diameter);
#ifdef DEBUG
    printf("\n[DEBUG][RESIZE] path after scaling and centering:\n");
    display_path(path);
    printf("\n");
#endif
    point_t c = {0, DIST_OC};
    move_path(path, &c);
    motor_offset = compute_motor_center(path);
}

point_t center_pos(void)
{
    point_t center = {
        ((M_PI / 2 + acos(DIST_OC / 2.0 / DIST_L)) * GEAR_RATIO - motor_offset.x) * 180 / M_PI,
        (M_PI - 2 * acos(DIST_OC / 2.0 / DIST_L)) * 180 / M_PI};
    return center;
}

point_t xy2recheable_angles(point_t point)
{
    point_t angles = xy2ab(point);
    angles.x -= motor_offset.x;
    angles.x *= 180 / M_PI;
    angles.y *= 180 / M_PI;
    return angles;
}
