#include "pack.h"


u8 *pack(scp_message *sm) {
    u16 *len = malloc(sizeof(u16));
    u8 *scp_data = encode_message(sm, len);
    u8 *udp_data = pack_scp(scp_data, len);
    u8 *ip_data = pack_udp(udp_data, len);
    u8 *ppp_data = pack_ip(ip_data, len);
    u8 *raw_data = pack_ppp(ppp_data, len);
    return raw_data;
}