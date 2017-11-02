#include "ax12.h"
#include <math.h>
#include <stdio.h>
#include "conf.h"
#include "coordinate.h"
#include "path.h"
#include "pump.h"
#ifndef DEBUG
#include <wiringPi.h>
#include "AX12/ax12.h"
#endif

static volatile int lock_1 = 1;
static volatile int lock_2 = 1;
static int          dist_before_stop_pump;

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
        default: printf("Unexpected error: %d\n", err);
    }
}

void move(point_t angles)
{
    float a = angles.x - AX12_OFFSET_A;
    float b = angles.y - AX12_OFFSET_B;
#ifdef DEBUG
    //printf("[INFO][MOVE] Go to [%f, %f]\n", a, b);
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
    lock_1  = 1;
    lock_2  = 1;
    int err = 1;
    for(int i = 0; i < AX12_NB_TRY && err != 0; i++)
        err = AX12move(AX12_ID_1, a, move_callback_1);
    handle_error(AX12_ID_1, err);
    err = 1;
    for(int i = 0; i < AX12_NB_TRY && err != 0; i++)
        err = AX12move(AX12_ID_2, b, move_callback_2);
    handle_error(AX12_ID_2, err);
    //while(lock_1 || lock_2);
#endif
}

/* Wait a user entry to continue
** This funtion is used to wait for the Nutella flow
*/
void wait_nutella(void)
{
    // Wait for the Nutella to flow
    printf("Press Any Key when Nutella is flowing\n");
    start_pump();
    getchar();
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
    int dist_from_beginning = 0;
    dist_before_stop_pump   = find_when_stop_pump(path);
    move(xy2recheable_angles(path->points[0]));
    wait_nutella();
    for(int i = 1; i < path->nb_points; i++) {
        dist_from_beginning += dist(path->points[i - 1], path->points[i]);
        if(i != 1 && dist_from_beginning > dist_before_stop_pump)
            stop_pump();
        smart_move(path->points[i - 1], path->points[i]);
    }
}
