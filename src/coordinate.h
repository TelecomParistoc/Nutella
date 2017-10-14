#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include "path.h"

/* Return angles positions of Nutella printer motors
** to reach each points of the path
** [in]  path: points to reach
** [in]  diameter: diameter of the 'crepe'
*/
void compute_path(path_t * path, int diameter);

#endif //_COORDINATE_H_
