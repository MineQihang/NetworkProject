#include "unpack.h"


scp_message *unpack(u8 *raw_data) {
    // 解封装
    u8 *ppp_data = unpack_ppp(raw_data);
    if(ppp_data == NULL) return NULL;
    u8 *ip_data = unpack_ip(ppp_data);
    if(ip_data == NULL) return NULL;
    u8 *udp_data = unpack_udp(ip_data);
    if(udp_data == NULL) return NULL;
    u8 *scp_data = unpack_scp(udp_data);
    scp_message *sm = decode_message(scp_data);
    return sm;
}