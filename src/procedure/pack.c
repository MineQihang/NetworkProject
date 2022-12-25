#include "pack.h"


u8* pack(scp_message* sm){
    u8* scp_data = encode_message(sm);
    printf("Hello");
    u8* udp_data = pack_scp(scp_data);
    u8* ip_data  = pack_udp(udp_data);
    u8* ppp_data = pack_ip(ip_data);
    u8* raw_data = pack_ppp(ppp_data);
    return raw_data;
}