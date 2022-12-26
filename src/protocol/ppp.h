#ifndef PPP_H
#define PPP_H

#include "../utils/common.h"

typedef struct ppp_header {
    u8  F;          // 定界符
    u8  A;          // 地址字段
    u8  C;          // 控制字段
    u16 protocol;   // 协议
} ppp_header;

typedef struct ppp_footer {
    u16 FCS;
    u8  F;
} ppp_footer;


u8 *pack_ppp(u8 *, u16 *);

u8 *unpack_ppp(u8 *);


#endif //PPP_H