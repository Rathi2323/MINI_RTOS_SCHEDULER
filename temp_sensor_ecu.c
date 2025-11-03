#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "temp_sensor_ecu.h"
#include "can_bus.h"
#include "color.h"

float get_temperature(void)
{
    static float temp = 25.0f;

    // random fluctuation between -1.5°C and +1.5°C
    //temp += ((rand() % 300) - 150) / 100.0f;
    temp += ((rand() % 500) - 250) / 100.0f; // -2.5 to +2.49 °C

    if (temp < 20.0f) temp = 20.0f;
    if (temp > 30.0f) temp = 30.0f;

    return temp;
}

void send_temperature(void)
{
    float temperature = get_temperature();
    unsigned int temp_x10 = (unsigned int)(temperature * 10);

    CAN_Frame frame;
    frame.id = 0x200;  // normal priority
    frame.length = 2;
    frame.type = MSG_TYPE_TEMPERATURE;
    frame.source = ECU_SENSOR;
    frame.data[0] = (temp_x10 >> 8) & 0xFF;
    frame.data[1] = temp_x10 & 0xFF;

    printf(MAGENTA"[TEMP_SENSOR]" RESET
           " Sending Temperature: %.1f degree Celsius -> Data [%02X %02X]\n",
           temperature, frame.data[0], frame.data[1]);

    can_send(&frame);
}
