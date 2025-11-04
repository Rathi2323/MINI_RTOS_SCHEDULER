Vehicle Sensor Network Simulator (CAN Bus in Software)

Concept:
Simulate multiple ECUs communicating over a virtual CAN bus. Each “ECU” runs as a thread or function that sends and receives messages.

Skills covered:

Structures for message framing

Threading (using pthread.h in Linux or simulation in single-threaded loop)

Data queues / message buffers

State machine design

Modular programming

Modules to implement:

can_bus.c — Virtual CAN driver (send/receive queue)

engine_ecu.c — Sends engine RPM periodically

temp_sensor_ecu.c — Sends temperature data

dashboard_ecu.c — Receives & displays messages

Integration:
All modules communicate via a shared queue (simulating CAN bus arbitration).

Possible extension:
Add error frames, message filtering, and logging.

Resume tagline example:

“Developed a virtual CAN bus simulator in C, implementing message arbitration, multi-node communication, and diagnostics between simulated ECUs using modular design and data structures.”


gcc main.c can_bus.c temp_sensor_ecu.c engine_ecu.c dashboard_ecu.c -o output/mini_rtos.exe
