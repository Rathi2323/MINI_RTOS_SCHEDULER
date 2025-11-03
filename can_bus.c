#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "can_bus.h"
#include "color.h"

#define MAX_QUEUE_SIZE 10
#define NUM_ECU 3

static CAN_Frame bus_buffer[MAX_QUEUE_SIZE];
static int queue_size = 0;
static int message_available = 0;
static int read_count = 0;

static int get_highest_priority_index(void)
{
    if (queue_size == 0)
        return -1;

    int min_idx = 0;
    for (int i = 1; i < queue_size; i++)
    {
        if (bus_buffer[i].id < bus_buffer[min_idx].id)
            min_idx = i;
    }
    return min_idx;
}

void can_send(const CAN_Frame *frame)
{
    if (queue_size < MAX_QUEUE_SIZE)
    {
        bus_buffer[queue_size++] = *frame;
        message_available = 1;
        read_count = 0;

        printf(YELLOW "[BUS]" RESET " Message received with id 0x%03X\n", frame->id);
        printf(YELLOW "[BUS]" RESET " Queue size now: %d\n", queue_size);
    }
    else
    {
        printf(YELLOW "[BUS]" RESET " Message dropped! Queue Full\n");
    }
}

int can_receive(CAN_Frame *frame)
{
    if (!message_available || queue_size == 0)
        return 0;

    int idx = get_highest_priority_index();
    *frame = bus_buffer[idx];
    read_count++;

    // simulate ECU consumption
    if (read_count >= NUM_ECU)
    {
        for (int i = idx; i < queue_size - 1; i++)
            bus_buffer[i] = bus_buffer[i + 1];

        queue_size--;
        read_count = 0;

        if (queue_size == 0)
            message_available = 0;

        printf(YELLOW "[BUS]" RESET " Frame (ID: 0x%03X) fully consumed and cleared\n", frame->id);
        printf(YELLOW "[BUS]" RESET " Queue size now: %d\n", queue_size);
    }
    return 1;
}
