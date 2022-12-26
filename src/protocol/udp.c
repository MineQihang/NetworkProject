#include "udp.h"
#include "ip.h"

fake_header* get_fake_header(u8* data, u16 udp_len) {
    ip_header header = *(ip_header *) data;
    fake_header* fheader = (fake_header*) malloc(sizeof(fake_header));
    fheader->saddr   = header.saddr;
    fheader->daddr   = header.daddr;
    fheader->field3  = 0;
    fheader->field4  = 17;
    fheader->udp_len = udp_len;
    return fheader;
}

u16 check_sum(u8* udp_data, u16 udp_len, u8* data){
    u32 sum = 0;
    u16* fheader = (u16*) get_fake_header(data, udp_len);
    for(int i = 0; i < sizeof(fake_header) / 2; i ++ )
        sum += fheader[i];
    u16* tmp = (u16*) udp_data;
    for(int i = 0; i < udp_len / 2; i ++)
        sum += tmp[i];
    if(udp_len & 1) sum += ((u32)udp_data[udp_len-1]) << 16;
    sum = (sum >> 16) + (sum << 16 >> 16);
    sum = (sum >> 16) + (sum << 16 >> 16);
    return (u16) ~sum;
}

u8 *pack_udp(u8 *data, u16 *len) {
    // 封装UDP数据报
    // 定义首部
    udp_header header = {
            .src_port = 2000,
            .des_port = 3000,
            .len      = *len,
            .sum      = 0
    };
    // 确定首部及数据大小
    size_t header_size = sizeof(header);
    size_t data_size = *len;
    *len = header_size + data_size;
    // 把首部和数据封装成数据报
    u8 *packed_data = malloc(*len);
    memcpy(packed_data, &header, header_size);
    memcpy(packed_data + header_size, data, data_size);
    header.sum = check_sum(packed_data, *len, data);
    memcpy(packed_data, &header, header_size);
//    printf("%d\n", header.sum);
    return packed_data;
}

u8 *unpack_udp(u8 *data) {
    // 解封装UDP数据报
    udp_header header = *(udp_header *) data;
    size_t header_size = sizeof(header);
    u8 *unpacked_data = data + header_size;
//    data[0] = 234;
    u16 sum = check_sum(data, header.len + header_size, unpacked_data);
    if(sum != 0) {
        printf("Error: UDP checksum is wrong!\n");
        return NULL;
    }
    return unpacked_data;
}
