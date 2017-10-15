#include <stdio.h>
#include "ax12.h"
#include "conf.h"
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
    switch(err){
        case -1: printf("Serial port not initialized\n");break;
        case -2: printf("Wrong checksum\n");break;
        case -3: printf("Target and answer ID mismatch\n");break;
        case -4: printf("Timeout\n");break;
        case -5: printf("Callback buffer is full\n");break;
        default: printf("Unexpected error\n");
    }
}

/* Move the AX12 to a position
** This is a blocking function
** [in]  a: rotation of the first motor
** [in]  b: rotation of the second motor
*/
static void move(float a, float b)
{
#ifdef DEBUG
    printf("[DEBUG][MOVE] Go to [%f, %f]\n", a, b);
#else
    handle_error(AX12_ID_1, AX12move(AX12_ID_1, a, move_callback_1));
    handle_error(AX12_ID_2, AX12move(AX12_ID_2, b - AX12_OFFSET_B, move_callback_2));
	while(lock_1 || lock_2);
#endif
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

void move_to(point_t pos)
{
    move(pos.x, pos.y);
}

void follow_path(path_t * path)
{
    for(int i = 0; i < path->nb_points; i++)
        move(path->points[i].x, path->points[i].y);
}
