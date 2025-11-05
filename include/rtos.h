#ifndef RTOS_H
#define RTOS_H

#include <stdint.h>

typedef void (*Taskfunction)(void);

typedef struct 
{
    Taskfunction task;
    uint32_t period_ms;
    uint32_t last_run;
}Task_t;

void RTOS_Init(void);
void RTOS_AddTask(Taskfunction task, uint32_t period_ms);
void RTOS_Run(void);

#endif
