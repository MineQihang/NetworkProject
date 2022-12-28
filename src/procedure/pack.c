#include "pack.h"

static void print_hex(u8* data, u16* len, char* str) {
    printf("%s", str);
    for(int i = 0; i < *len; i ++ ){
        if(i % 8 == 0) printf("\n");
        printf("0x%02X ", data[i]);
    };
    printf("\n\n");
}

u8 *pack(scp_message *sm, u16 *len) {
    // 封装
    u8 *scp_data = encode_message(sm, len);
    u8 *udp_data = pack_scp(scp_data, len);
    if(show_proc) print_hex(udp_data, len, "packed scp");
    u8 *ip_data = pack_udp(udp_data, len);
    if(show_proc) print_hex(ip_data, len, "packed udp");
    u8 *ppp_data = pack_ip(ip_data, len);
    if(show_proc) print_hex(ppp_data, len, "packed ip");
    u8 *raw_data = pack_ppp(ppp_data, len);
    if(show_proc) print_hex(raw_data, len, "packed ppp");
    return raw_data;
}