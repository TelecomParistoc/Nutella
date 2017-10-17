#include "coordinate.h"
#include <math.h>
#include <stdio.h>
#include "conf.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Offset of the motors positions
static float motor_offset_a;

/* Return the squared distance between a point and the origin
** [in]  point to compute
*/
static inline int dist2(point_t point)
{
    return (point.x * point.x + point.y * point.y);
}

/* Change coordinates from cartesian to polar
** [in]  point: cartesian coordinates
** [out] polar coordinates
*/
static point_t xy2rt(point_t point)
{
    point_t p = {
        sqrt(dist2(point)),
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
    int r = dist2(path->points[0]);
    int dist;
    for(int i = 1; i < path->nb_points; i++)
        if((dist = dist2(path->points[i])) > r)
            r = dist;
    // Scale points to fit them into C
    float ratio = diameter / 2.0 / sqrt(r);
    for(int i = 0; i < path->nb_points; i++) {
        path->points[i].x *= ratio;
        path->points[i].y *= ratio;
    }
}

/* Return the path in angles coordinates in deg
** Usable by the Nutella printer
** [in]  path: points to compute
*/
static void xy2angles_path(path_t* path)
{
    // Get coordinates as polar
    for(int i = 0; i < path->nb_points; i++)
        path->points[i] = xy2rt(path->points[i]);
    // Get angles of the motors to reach each points
    float b;
    for(int i = 0; i < path->nb_points; i++) {
        b                 = M_PI - 2 * acos(path->points[i].x / 2.0 / DIST_L);
        path->points[i].x = GEAR_RATIO * (path->points[i].y + (M_PI - b) / 2);
        path->points[i].y = b;
    }
    // Get center angles for a
    float min_a = path->points[0].x;
    float max_a = min_a;
    for(int i = 0; i < path->nb_points; i++) {
        if(path->points[i].x > max_a)
            max_a = path->points[i].x;
        else if(path->points[i].x < min_a)
            min_a = path->points[i].x;
    }
    motor_offset_a = (min_a + max_a) / 2;
    // Center angles
    for(int i = 0; i < path->nb_points; i++)
        path->points[i].x -= motor_offset_a;
    // Change to deg instead of rad
    for(int i = 0; i < path->nb_points; i++) {
        path->points[i].x *= 180 / M_PI;
        path->points[i].y *= 180 / M_PI;
    }
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
#endif
    point_t c = {0, DIST_OC};
    move_path(path, &c);
    xy2angles_path(path);
#ifdef DEBUG
    printf("\n[DEBUG][ANGLE] path with coordinates of motors:\n");
    display_path(path);
    printf("\n");
#endif
}

point_t center_pos(void)
{
    point_t center = {
        ((M_PI / 2 + acos(DIST_OC / 2.0 / DIST_L)) * GEAR_RATIO - motor_offset_a) * 180 / M_PI,
        (M_PI - 2 * acos(DIST_OC / 2.0 / DIST_L)) * 180 / M_PI};
    return center;
}
