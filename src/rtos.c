#include "rtos.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_TASKS 5

static Task_t tasks[MAX_TASKS];
static uint8_t task_count = 0;

static uint32_t millis(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000)+(ts.tv_nsec/1000000);
}

void RTOS_Init(void)
{
    task_count=0;
}
void RTOS_AddTask(Taskfunction task, uint32_t period_ms)
{
    if(task_count < MAX_TASKS)
    {
        tasks[task_count].task = task;
        tasks[task_count].period_ms = period_ms;
        tasks[task_count].last_run = millis();
        task_count++;
    }
}
void RTOS_Run(void)
{
    while(1)
    {
        uint32_t now = millis();
        for(int i=0;i<task_count;i++)
        {
            if((now-tasks[i].last_run) >= tasks[i].period_ms)
            {
                tasks[i].task();
                tasks[i].last_run = now;
            }
        }
    }
}