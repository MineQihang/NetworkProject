#ifndef SCP_H
#define SCP_H

#include "../utils/common.h"

typedef struct scp_header {
    u8* len_message;
} scp_header;

typedef struct scp_datagram{
    scp_header* header;
    u8* data;
} scp_datagram;

typedef struct scp_message{
    char* sender_name;
    char* message;
} scp_message;

u8* pack_scp(u8* );

u8* unpack_scp(u8* );

u8* encode_message(scp_message* );

scp_message* decode_message(u8* );

#endif //SCP_H