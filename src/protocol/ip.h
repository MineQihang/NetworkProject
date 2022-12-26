#ifndef IP_H
#define IP_H

#include "../utils/common.h"

typedef struct ip_header {
    u8  version: 4, // 版本
        hlen: 4;    // 首部长度
    u8  ds;         // 区分服务
    u16 tlen;       // 总长度
    u16 id;         // 标识
    u16 flag_off;   // 标志 + 片偏移
    u8  ttl;        // 生存时间
    u8  protocol;   // 协议
    u16 hsum;       // 首部检验和
    u32 saddr;      // 源地址
    u32 daddr;      // 目的地址
} ip_header;


u8 *pack_ip(u8 *, u16 *);

u8 *unpack_ip(u8 *);


#endif //IP_H