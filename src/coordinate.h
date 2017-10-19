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

#endif //_COORDINATE_H_
