#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include "path.h"

/* Resize and rescale a group of points to fit them in a circle
** [in]  path: group of points to resize
** [in]  diamter: diameter of the container circle
*/
void resize_coordinates(path_t * path, int diameter);

/* Change coordinates from cartesian to polar
** [in]  point: cartesian coordinates
** [out] polar coordinates
*/
point_t xy2rt(point_t point);

#endif //_COORDINATE_H_
