#ifndef PACK_H
#define PACK_H

#include "../protocol/ppp.h"
#include "../protocol/ip.h"
#include "../protocol/udp.h"
#include "../protocol/scp.h"

u8 *pack(scp_message *, u16 *);

#endif //PACK_H