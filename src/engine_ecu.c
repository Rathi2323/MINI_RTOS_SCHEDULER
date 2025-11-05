#include <stdio.h>
#include <stdlib.h>
#include "engine_ecu.h"
#include "can_bus.h"
#include "color.h"

static int warn_activity = 0;

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

        CAN_Frame warnframe;   
        warnframe.length = 2;
        warnframe.data[0]=tempframe.data[0];
        warnframe.data[1]=tempframe.data[1]; 
        warnframe.source = ECU_ENGINE;    
        if(!warn_activity && temperature > 25.f)
            {
            warn_activity = 1;
            warnframe.id = 0x100;
            warnframe.type = MSG_TYPE_WARNING;
            can_send(&warnframe);
            }
        else if(warn_activity && temperature < 23.f)
        {
             warn_activity = 0;
             warnframe.id = 0x150;
             warnframe.type = MSG_TYPE_TEMPERATURE;
             can_send(&warnframe);
        }
        else
        {
            warnframe.id = warn_activity ? 0x100 : 0x150;
            warnframe.type = warn_activity ? MSG_TYPE_WARNING : MSG_TYPE_TEMPERATURE;
            can_send(&warnframe);
        }
        return 1;
     }

   }
  else
  {
    printf(CYAN"[ENGINE ECU]" RESET "No Message Received:(\n");
  }
  return 0;
}