#include "udp.h"

u8 *pack_udp(u8 *data, u16 *len) {
    // 封装UDP数据报
//    // 定义首部
//    udp_header header = {
//            .src_port = 0,
//            .des_post = 0,
//            .len      = 0,
//            .sum      = 0
//    };
//    // 确定首部及数据大小
//    size_t header_size = sizeof(header);
//    size_t data_size = strlen(data);
//    printf("%d\n", sizeof(data));
//    // 把首部和数据封装成数据报
//    u8 *packed_data = malloc(header_size + data_size + 1);
//    memcpy(packed_data, &header, header_size);
//    strcpy((char *) packed_data + header_size, data);
    return data;
}

u8 *unpack_udp(u8 *data) {
    // 解封装UDP数据报
//    udp_header header = *(udp_header *) data;
//    size_t header_size = sizeof(header);
//    u8 *unpacked_data = data + header_size;
    return data;
}
