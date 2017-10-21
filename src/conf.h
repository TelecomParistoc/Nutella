#ifndef _CONF_H_
#define _CONF_H_

/***********************************
********** MODEL GEOMETRY **********
***********************************/

// Distance between origin and 'crepe' center
#define DIST_OC         260
// Distance of the arm
#define DIST_L          220
// Gear ratio
#define GEAR_RATIO      3

/***********************************
*************** AX12 ***************
***********************************/

// AX12 baudrate
#define AX12_BAUDRATE   115200
// First AX12 id
#define AX12_ID_1       141
// Second AX12 id
#define AX12_ID_2       135
// Torque (in %)
#define AX12_TORQUE     50
// Second AX12 offset
#define AX12_OFFSET_A   0
#define AX12_OFFSET_B   47.16
// Min and max positions of AX12s
#define AX12_MIN_A      -150
#define AX12_MAX_A      150
#define AX12_MIN_B      -20
#define AX12_MAX_B      105

/***********************************
*************** PATH ***************
***********************************/

// Distance between two points of the path in mm
// This step is used during path interpolation
// to make the path linear
#define PATH_DIST       3

#endif //_CONF_H_
