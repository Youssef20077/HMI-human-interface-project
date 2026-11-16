#ifndef SENSORS_H
#define SENSORS_H
#include <stdint.h>
extern uint16_t low_limit[3];
extern uint16_t high_limit[3];
extern uint16_t readings[3];
extern uint8_t valid[3];
void Sensors_Init(void);
void Sensors_UpdateAnalog(void);
void Sensors_UpdateHumidity(void);
uint8_t Sensors_Alarm(uint8_t sensor);
#endif
