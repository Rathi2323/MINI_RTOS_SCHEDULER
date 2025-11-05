# MINI_RTOS_SCHEDULER

A mini RTOS-inspired scheduler simulation for ECU communication via CAN bus

Build command: gcc -o output/MiniRTOS.exe main.c ecu_engine.c ecu_sensor.c can_bus.c dashboard_ecu.c -Iinclude

Flow chart: [TEMP SENSOR ECU] → [CAN BUS] → [ENGINE ECU] → [DASHBOARD ECU]
