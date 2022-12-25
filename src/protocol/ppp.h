#ifndef PPP_H
#define PPP_H

#include "../utils/common.h"

typedef struct ppp_header {
    u8* len_message;
} ppp_header;

typedef struct ppp_datagram{
    ppp_header* header;
    u8* data;
} ppp_datagram;

u8* pack_ppp(u8* );

u8* unpack_ppp(u8* );


#endif //PPP_H