#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "can_bus.h"
#include "temp_sensor_ecu.h"
#include "engine_ecu.h"
#include "dashboard_ecu.h"
#include "color.h"
#include "rtos.h"

void Task_TempSensor(void)
{
    send_temperature();
}
void Task_EngineECU(void)
{
    check_temperature();
}
void Task_Dashboard(void)
{
    dashboard_view();
}
int main(void)
{
    srand(time(NULL));   // stronger random seeding

    //printf("=== Temperature Sensor ECU simulation ===\n");
    CAN_Init();
    RTOS_Init();

   /* CAN_Frame received;
    if (can_receive(&received))
        printf(BLUE"[MAIN]"RESET " Message consumed from bus (ID: 0x%03X)\n", received.id);

    printf("\n=== Simulation complete ===\n");
    printf("\nPress Enter to exit...");
    getchar();*/
     // Add periodic tasks
    RTOS_AddTask(Task_TempSensor, 1000);   // every 1 second
    RTOS_AddTask(Task_EngineECU,  1100);   // every 0.5 seconds
    RTOS_AddTask(Task_Dashboard,  1200);   // every 0.5 seconds

    printf(YELLOW "\n=== RTOS-based CAN Simulation Started ===\n" RESET);

    RTOS_Run();  // this never returns

    return 0;
}
