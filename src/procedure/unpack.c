#include "unpack.h"


scp_message *unpack(u8 *raw_data) {
    // 解封装
    u8 *ppp_data = unpack_ppp(raw_data);  // 得到ppp的数据
    if(ppp_data == NULL) return NULL;     // 丢弃无效数据
    u8 *ip_data = unpack_ip(ppp_data);    // 得到ip的数据
    if(ip_data == NULL) return NULL;      // 丢弃无效数据
    u8 *udp_data = unpack_udp(ip_data);   // 得到udp的数据
    if(udp_data == NULL) return NULL;     // 丢弃无效数据
    u8 *scp_data = unpack_scp(udp_data);  // 得到scp的数据
    scp_message *sm = decode_message(scp_data);  // 解码
    return sm;
}