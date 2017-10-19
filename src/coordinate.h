#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include "path.h"

/* Return angles positions of Nutella printer motors
** to reach each points of the path
** [in]  path: points to reach
** [in]  diameter: diameter of the 'crepe'
*/
void compute_path(path_t * path, int diameter);

/* Get angle position to reach
** the center position the the crepe
** Must be called after 'compute_path' function
*/
point_t center_pos(void);

/* Convert cartesian coordinate to reachable angles by motors
** [in]  point: point in cartesian coordinates
** [out] angles reachable by motors
*/
point_t xy2recheable_angles(point_t point);

/* Return distance between two points
** [in]  p1: first point
** [in]  p2: second point
** [out] distance between two points
*/
float dist(point_t p1, point_t p2);

#endif //_COORDINATE_H_
