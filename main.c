#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "can_bus.h"
#include "temp_sensor_ecu.h"
#include "engine_ecu.h"
#include "dashboard_ecu.h"
#include "color.h"

int main(void)
{
    srand(time(NULL) ^ getpid());   // stronger random seeding

    printf("=== Temperature Sensor ECU simulation ===\n");

    for (int i = 0; i < 10; i++)
    {
        send_temperature();
        sleep(1);

        check_temperature();
        sleep(1);

        dashboard_view();
        sleep(1);

        CAN_Frame received;
        if (can_receive(&received))
            printf(BLUE"[MAIN]"RESET " Message consumed from bus (ID: 0x%03X)\n", received.id);

        sleep(1);
    }

    printf("\n=== Simulation complete ===\n");
    printf("\nPress Enter to exit...");
    getchar();
    return 0;
}
