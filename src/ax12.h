#ifndef _AX12_H_
#define _AX12_H_

#include "path.h"

/* Initialize AX12
** into default mode (not wheel mode)
** with acceptable torque
*/
void init_ax12(void);

/* Move the AX12 to a position
** This is a blocking function
** a: rotation of the first motor
** b: rotation of the second motor
** [in]  angles: move to [a,b]
*/
void move(point_t angles);

/* Follow a path with the AX12s
** Between two points, linear interpolation is done to make the path smoother
** [in]  path: path to follow
** [in]  step: linear interpolation step
*/
void follow_path(path_t * path, int step);

#endif // _AX12_H_
