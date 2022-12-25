#ifndef IP_H
#define IP_H

#include "../utils/common.h"

typedef struct ip_header {
    u8* len_message;
} ip_header;

typedef struct ip_datagram{
    ip_header* header;
    u8* data;
} ip_datagram;

u8* pack_ip(u8* );

u8* unpack_ip(u8* );


#endif //IP_H