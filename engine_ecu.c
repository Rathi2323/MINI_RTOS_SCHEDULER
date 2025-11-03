#include <stdio.h>
#include <stdlib.h>
#include "engine_ecu.h"
#include "can_bus.h"
#include "color.h"

int check_temperature()
{
  CAN_Frame tempframe;

  if(can_receive(&tempframe))
  {
    if(tempframe.source == ECU_SENSOR && tempframe.type == MSG_TYPE_TEMPERATURE)
    {
        unsigned int temp_x10 = ((tempframe.data[0]<<8)|tempframe.data[1]);
        float temperature = temp_x10/10.0f;

        printf(CYAN"[ENGINE ECU]" RESET "Temperature Check\n");
        if(temperature > 25.f)
            {
            CAN_Frame warnframe;
            warnframe.id = 0x100;
            warnframe.length = 2;
            warnframe.type = MSG_TYPE_WARNING;
            warnframe.source = ECU_ENGINE;
            warnframe.data[0]=tempframe.data[0];
            warnframe.data[1]=tempframe.data[1];
            can_send(&warnframe);
            return 1;
            }
     }

   }
  else
  {
    printf(CYAN"[ENGINE ECU]" RESET "No Message Received:(\n");
  }
  return 0;
}