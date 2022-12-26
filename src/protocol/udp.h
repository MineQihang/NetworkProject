#ifndef UDP_H
#define UDP_H

#include "../utils/common.h"

typedef struct udp_header {
    u16 src_port;  // 源端口
    u16 des_post;  // 目的端口
    u16 len;       // 长度
    u16 sum;       // 校验和
} udp_header;

u8 *pack_udp(u8 *, u16 *);

u8 *unpack_udp(u8 *);


#endif //UDP_H