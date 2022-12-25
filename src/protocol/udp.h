#ifndef UDP_H
#define UDP_H

#include "../utils/common.h"

typedef struct udp_header {
    u8* len_message;
} udp_header;

typedef struct udp_datagram{
    udp_header* header;
    u8* data;
} udp_datagram;

u8* pack_udp(u8* );

u8* unpack_udp(u8* );


#endif //UDP_H