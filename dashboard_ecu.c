#include <stdio.h>
#include "can_bus.h"
#include "dashboard_ecu.h"
#include "color.h"

void dashboard_view()
{
    static int last_state = -1;  // -1 = none, 0 = normal, 1 = warning
    CAN_Frame dashview;

    if (can_receive(&dashview))
    {
        unsigned int temp_x10 = ((dashview.data[0] << 8) | dashview.data[1]);
        float temperature = temp_x10 / 10.0f;

        printf(BLUE "\n[DASHBOARD REVIEW]: " RESET);

        if (dashview.type == MSG_TYPE_WARNING)
        {
            if (last_state != 1)
            {
                printf(RED "WARNING!! TEMPERATURE HIGH!! (Above 25 Degree Celsius)\n" RESET);
                last_state = 1;
            }
            printf(RED "WARNING PERSISTS!! Current Temperature: %.1f Degree Celsius\n" RESET, temperature);
        }
        else if (dashview.type == MSG_TYPE_TEMPERATURE)
        {
            if (last_state != 0)
            {
                printf(GREEN "Temperature returned to NORMAL range.\n" RESET);
                last_state = 0;
            }
            printf(GREEN "Current Temperature: %.1f Degree Celsius\n" RESET, temperature);
        }
    }
}
