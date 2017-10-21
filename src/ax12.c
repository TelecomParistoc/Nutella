#include "ax12.h"
#include <math.h>
#include <stdio.h>
#include "conf.h"
#include "coordinate.h"
#include "path.h"
#ifndef DEBUG
#include "AX12/ax12.h"
#endif

static int lock_1 = 1;
static int lock_2 = 1;

/* First AX12 Move callback
*/
static void move_callback_1(void)
{
    lock_1 = 0;
}

/* Second AX12 Move callback
*/
static void move_callback_2(void)
{
    lock_2 = 0;
}

/* Print error message if an error occured
** [in]  ax12_id: ID of the source AX12
** [in]  err: error code (could be 0 for no error)
*/
static void handle_error(int ax12_id, int err)
{
    if(err == 0)
        return;
    printf("[ERROR][AX12] (id: %d) AX12move ERROR: (%d) ", ax12_id, err);
    switch(err) {
        case -1: printf("Serial port not initialized\n"); break;
        case -2: printf("Wrong checksum\n"); break;
        case -3: printf("Target and answer ID mismatch\n"); break;
        case -4: printf("Timeout\n"); break;
        case -5: printf("Callback buffer is full\n"); break;
        default: printf("Unexpected error\n");
    }
}

void move(point_t angles)
{
    float a = angles.x - AX12_OFFSET_A;
    float b = angles.y - AX12_OFFSET_B;
#ifdef DEBUG
    printf("[INFO][MOVE] Go to [%f, %f]\n", a, b);
#endif
    if(a > AX12_MAX_A || a < AX12_MIN_A) {
        printf("[ERROR][MOVE] AX12 1, Unreachable value: %f\n", a);
        return;
    }
    if(b > AX12_MAX_B || b < AX12_MIN_B) {
        printf("[ERROR][MOVE] AX12 2, Unreachable value: %f\n", b);
        return;
    }
#ifndef DEBUG
    lock_1 = 1;
    lock_2 = 1;
    handle_error(AX12_ID_1, AX12move(AX12_ID_1, a, move_callback_1));
    handle_error(AX12_ID_2, AX12move(AX12_ID_2, b, move_callback_2));
    while(lock_1 || lock_2)
        ;
#endif
}

/* Move from a point to another using linear interpolation
** [in]  p1: start point
** [in]  p2: end point
*/
static void smart_move(point_t p1, point_t p2)
{
    printf("Go from [%f,%f] to [%f,%f]\n", p1.x, p1.y, p2.x, p2.y);
    float   d         = dist(p1, p2);
    int     nb_step   = (int)(d / PATH_DIST + 0.5);
    point_t vect_step = {(p2.x - p1.x) * PATH_DIST / d, (p2.y - p1.y) * PATH_DIST / d};
    for(int i = 0; i < nb_step; i++) {
        move(xy2recheable_angles(p1));
        p1.x += vect_step.x;
        p1.y += vect_step.y;
    }
}

void init_ax12(void)
{
#ifndef DEBUG
    initAX12(AX12_BAUDRATE);
    AX12setMode(AX12_ID_1, DEFAULT_MODE);
    AX12setMode(AX12_ID_2, DEFAULT_MODE);
    AX12setTorque(AX12_ID_1, AX12_TORQUE);
    AX12setTorque(AX12_ID_2, AX12_TORQUE);
#endif
}

void follow_path(path_t* path)
{
    for(int i = 1; i < path->nb_points; i++)
        smart_move(path->points[i - 1], path->points[i]);
}
