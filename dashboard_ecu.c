#include <stdio.h>
#include "can_bus.h"
#include "dashboard_ecu.h"
#include "color.h"

void dashboard_view()
{
    CAN_Frame dashview;

    if(can_receive(&dashview))
    {
        unsigned int temp_x10 = ((dashview.data[0]<<8)|dashview.data[1]);
        float temperature = temp_x10/10.0f;
        printf("\n[DASHBOARD REVIEW]: ");
        if(dashview.source == ECU_SENSOR && dashview.type == MSG_TYPE_TEMPERATURE)
        {
            printf(GREEN"Temperature levels are Normal!! Current Temperature is : %f\n",temperature);
        }
        else if(dashview.source == ECU_ENGINE && dashview.type == MSG_TYPE_WARNING)
        {
            printf(RED"WARNING!! TEMPERATURE HIGH!! Current Temperature is : %f\n",temperature);
        }
    }
}