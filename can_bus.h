#ifndef CAN_BUS_H
#define CAN_BUS_H

#define CAN_MAX_DATA_LEN 8

typedef enum{
    MSG_TYPE_TEMPERATURE = 0X200,
    MSG_TYPE_WARNING     = 0X100
}MessageType;

typedef enum{
    ECU_SENSOR = 1,
    ECU_ENGINE = 2,
    ECU_DASHBOARD = 3
}ECU_Source;

typedef struct 
{
    unsigned int id;
    unsigned char length;
    unsigned char data[CAN_MAX_DATA_LEN];
    MessageType type;
    ECU_Source source;
}CAN_Frame;

void can_send(const CAN_Frame *frame); 
int can_receive(CAN_Frame *frame);
#endif
