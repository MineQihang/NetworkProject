#include "pack.h"


u8 *pack(scp_message *sm, u16 *len) {
    // 封装
    u8 *scp_data = encode_message(sm, len);
//    for(int i = 0; i < *len; i ++ ){
//        if(i % 8 == 0) printf("\n");
//        printf("0x%02X ", scp_data[i]);
//    };
//    printf("\n\n");
    u8 *udp_data = pack_scp(scp_data, len);
    u8 *ip_data  = pack_udp(udp_data, len);
    u8 *ppp_data = pack_ip(ip_data, len);
    u8 *raw_data = pack_ppp(ppp_data, len);
    return raw_data;
}