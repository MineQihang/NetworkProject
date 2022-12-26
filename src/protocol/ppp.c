#include "ppp.h"

u8 *pack_ppp(u8 *data, u16 *len) {
    // 封装PPP帧
    // 定义首部
    ppp_header header = {
            .F          =   0x7E,
            .A          =   0xFF,
            .C          =   0x03,
            .protocol   =   0x0021  // 上层是IP数据报
    };
    // 定义尾部
    ppp_footer footer = {
            .FCS        =   0,
            .F          =   0x7E
    };
    // 确定首部、数据、尾部大小
    size_t header_size  = sizeof(header);
    size_t data_size    = *len;
    size_t footer_size  = sizeof(footer);
    *len = header_size + 2 * data_size + footer_size;
    // 把首部封装到帧
    u8 *packed_data = malloc(*len);
    memcpy(packed_data, &header, header_size);
    // 字节填充
    size_t j = 0;
    u8 *p = packed_data + header_size;
    for(int i = 0; i < data_size; i++){
//        if(i < 10) printf("0x%X\n", data[i]);
        if(data[i] == 0x7E) p[j++] = 0x7D, p[j++] = 0x5E;
        else if(data[i] == 0x7D) p[j++] = 0x7D, p[j++] = 0x5D;
        else if(data[i] <  0x20) p[j++] = 0x7D, p[j++] = data[i] + 0x20;
        else p[j++] = data[i];
    }
//    for(int i=0;i <10; i++) {
//        printf("0x%X\n", *(packed_data + header_size + i));
//    }
    // 由于这里不是在SONET/SDH链路上，因此不实现零比特填充
    data_size = j;
    *len = header_size + data_size + footer_size;
    // 插入尾部
    memcpy(packed_data + header_size + j, &footer, footer_size);
//    printf("0x%X\n", *(packed_data + header_size + 2));
    return packed_data;
}

u8 *unpack_ppp(u8 *data) {
    // 解封装PPP帧
    ppp_header header = *(ppp_header *) data;
    size_t header_size = sizeof(header);
    u8 *unpacked_data = (u8*) malloc(1500);
    u8 *p = data + header_size;
    size_t j = 0;
    // 字节填充后要解码
    while(1) {
//        printf("0x%X\n", *p);
        if(*p == 0x7D) {
            ++ p;
            if(*p == 0x5E) unpacked_data[j++] = 0x7E;
            else if(*p == 0x5D) unpacked_data[j++] = 0x7D;
            else unpacked_data[j++] = *p - 0x20;
        }
        else if(*p == 0x7E) break;
        else unpacked_data[j++] = *p;
        ++ p;
    }
//    printf("%d\n", p - data);
    return unpacked_data;
}
