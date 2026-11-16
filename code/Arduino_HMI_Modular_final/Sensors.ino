#include "Sensors.h"
#include "ADC.h"
#include "DHT11.h"

#define LM35_ADC_REFERENCE_MV 5000UL
#define LM35_MAX_VALID_C 150U
uint16_t low_limit[3] = {20, 30, 200};
uint16_t high_limit[3] = {38, 70, 800};
uint16_t readings[3] = {0, 0, 0};
uint8_t valid[3] = {0, 0, 0};

void Sensors_Init(void) {}
void Sensors_UpdateAnalog(void)
{
    uint16_t raw = ADC_Average(0);
    uint32_t millivolts = ((uint32_t)raw * LM35_ADC_REFERENCE_MV + 511UL) / 1023UL;
    uint16_t temperature_c = (uint16_t)((millivolts + 5UL) / 10UL);
    readings[0] = temperature_c;
    valid[0] = (temperature_c <= LM35_MAX_VALID_C);
    readings[2] = ADC_Average(1);
    valid[2] = 1;
}
void Sensors_UpdateHumidity(void)
{
    uint8_t humidity;
    if (DHT11_ReadHumidity(&humidity))
    {
        readings[1] = humidity;
        valid[1] = 1;
    }
    else valid[1] = 0;
}
uint8_t Sensors_Alarm(uint8_t sensor)
{
    return valid[sensor] &&
        (readings[sensor] < low_limit[sensor] || readings[sensor] > high_limit[sensor]);
}
