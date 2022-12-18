#ifndef UNPACK_H
#define UNPACK_H

#include "../protocol/ppp.h"
#include "../protocol/ip.h"
#include "../protocol/udp.h"
#include "../protocol/scp.h"


scp_datagram* unpack(u8* sd);

#endif //UNPACK_H
