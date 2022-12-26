#include "ip.h"

u8 *pack_ip(u8 *data, u16 *len) {
    // 封装IP数据报
    // 定义首部
    ip_header header = {
            .version    =   4,
            .hlen       =   4,
            .ds         =   0,
            .tlen       =   0,
            .id         =   0,
            .flag_off   =   0,
            .ttl        =   0,
            .protocol   =   0,
            .hsum       =   0,
            .saddr      =   0,
            .daddr      =   1
    };
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
    size_t header_size = sizeof(header);
    u8 *unpacked_data = data + header_size;
    return unpacked_data;
}
