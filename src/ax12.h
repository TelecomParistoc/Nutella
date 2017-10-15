#ifndef _AX12_H_
#define _AX12_H_

#include "path.h"

/* Initialize AX12
** into default mode (not wheel mode)
** with acceptable torque
*/
void init_ax12(void);

/* Move the AX12 to a position
** position must be two angles, one for each motor
** [in]  pos: angles of the two motors
*/
void move_to(point_t pos);

/* Follow a path with the AX12s
** [in]  path: path to follow
*/
void follow_path(path_t * path);

#endif // _AX12_H_
