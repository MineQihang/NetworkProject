#ifndef UDP_H
#define UDP_H

#include "../utils/common.h"

typedef struct udp_header {
    u16 src_port;  // 源端口
    u16 des_port;  // 目的端口
    u16 len;       // 长度
    u16 sum;       // 校验和
} udp_header;

typedef struct fake_header {
    u32 saddr;      // 源IP地址
    u32 daddr;      // 目的IP地址
    u8  field3;     // 第三字段
    u8  field4;     // 第四字段
    u16 udp_len;    // udp长度
} fake_header;

u8 *pack_udp(u8 *, u16 *);

u8 *unpack_udp(u8 *);


#endif //UDP_H