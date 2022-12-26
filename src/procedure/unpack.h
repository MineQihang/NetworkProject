#ifndef UNPACK_H
#define UNPACK_H

#include "../protocol/ppp.h"
#include "../protocol/ip.h"
#include "../protocol/udp.h"
#include "../protocol/scp.h"


scp_message *unpack(u8 *);

#endif //UNPACK_H
