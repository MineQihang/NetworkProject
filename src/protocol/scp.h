#ifndef SCP_H
#define SCP_H

#include "../utils/common.h"

typedef struct scp_datagram{
    char* message;
    char* sender_name;
} scp_datagram;

#endif //SCP_H