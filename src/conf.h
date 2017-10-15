#ifndef _CONF_H_
#define _CONF_H_

// Debug enabling
// Comment this line to disable debug
#define DEBUG           1

// Distance between origin and 'crepe' center
#define DIST_OC         260
// Distance of the arm
#define DIST_L          220
// Gear ratio
#define GEAR_RATIO      3

// AX12 baudrate
#define AX12_BAUDRATE   115200
// First AX12 id
#define AX12_ID_1       141
// Second AX12 id
#define AX12_ID_2       135
// Torque (in %)
#define AX12_TORQUE     50
// First AX12 offset
#define AX12_OFFSET_B   132.84
// First AX12 offset
#define AX12_OFFSET_A   70.73
// Min and max positions of AX12s
#define AX12_MIN_A      -150
#define AX12_MAX_A      150
#define AX12_MIN_B      -20
#define AX12_MAX_B      105

#endif //_CONF_H_
