#ifndef _PUMP_H_
#define _PUMP_H_

/* Initialize WiringPi and pump
** [out] return if an error occured
*/
int init_pump(void);

/* Activate the pump
*/
void start_pump(void);

/* Disactivate the pump
*/
void stop_pump(void);

#endif // _PUMP_H_
