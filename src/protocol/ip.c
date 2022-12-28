#include "ip.h"

u16 id = 0;

u16 check_sum_ip(ip_header* header){
    u32 sum = 0;
    u16* hdata = (u16*) header;
    for(int i = 0; i < sizeof(ip_header) / 2; i ++ )
        sum += hdata[i];
    sum = (sum >> 16) + (sum & 0x0000ffff);
    sum = (sum >> 16) + (sum & 0x0000ffff);
    return (u16) ~sum;
}

u8 *pack_ip(u8 *data, u16 *len) {
    // 封装IP数据报
    // 定义首部
    ip_header header = {
            .version    =   4,
            .hlen       =   5,
            .ds         =   0,
            .tlen       =   sizeof(header) + *len,
            .id         =   id++,
            .flag_off   =   0,
            .ttl        =   255,
            .protocol   =   17,
            .hsum       =   0,
            .saddr      =   0x11223344,
            .daddr      =   0x44332211
    };
    // 计算首部校验和
    header.hsum = check_sum_ip(&header);
    // 确定首部及数据大小
    size_t header_size = sizeof(header);
    size_t data_size = *len;
    *len = header_size + data_size;
    // 把首部和数据封装成数据报
    u8 *packed_data = malloc(*len);
    memcpy(packed_data, &header, header_size);
    memcpy(packed_data + header_size, data, data_size);
    return packed_data;
}

u8 *unpack_ip(u8 *data) {
    // 解封装IP数据报
    ip_header header = *(ip_header *) data;
    // 打印IP数据报
    if(show_proc) {
        printf("unpack: ip datagram");
        for (int i = 0; i < header.tlen; i++) {
            if (i % 8 == 0) printf("\n");
            printf("0x%02X ", data[i]);
        }
        printf("\n\n");
    }
    // header.daddr = 0x12345678;
    u16 sum = check_sum_ip(&header);
    if(sum != 0) {
        printf("Error: IP checksum is wrong!\n");
        return NULL;
    }
    size_t header_size = sizeof(header);
    u8 *unpacked_data = data + header_size;
    return unpacked_data;
}
