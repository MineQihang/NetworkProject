#include "scp.h"

u8 *pack_scp(u8 *data, const u16 *len) {
    // 封装SCP数据报
    scp_header header = {
            .len = *len,
            .send_time = 32
    };
    size_t header_size = sizeof(header);
    size_t data_size = *len;
    printf("data_size: %d\n", data_size);
    u8 *packed_data = malloc(header_size + data_size);
    memcpy(packed_data, &header, header_size);
    memcpy(packed_data + header_size, data, data_size);
    return packed_data;
}

u8 *unpack_scp(u8 *data) {
    // 解封装SCP数据报
    scp_header header = *(scp_header *) data;
    size_t header_size = sizeof(header);
    printf("len: %d\n", header.len);
    printf("send_time: %d\n", header.send_time);
    u8 *unpacked_data = data + header_size;
    return unpacked_data;
}

u8 *encode_message(scp_message *sm, u16 *len) {
    // 使用LV方式编码message
    char *sender_name = sm->sender_name;
    char *message = sm->message;

    printf("sender_name: %s\n", sender_name);
    printf("message: %s\n", message);

    size_t len_sn = strlen(sender_name) + 1;
    size_t len_m = strlen(message) + 1;

    *len = (u16) sizeof(len_sn) + len_sn + sizeof(len_m) + len_m;
    printf("sizeof encoded message: %d\n", *len);

    u8 *res = (u8 *) malloc(*len);
    size_t p = 0;
    memcpy(res + p, &len_sn, sizeof(len_sn));
    p += sizeof(len_sn);
    strcpy((char *) res + p, sender_name);
    p += len_sn;
    memcpy(res + p, &len_m, sizeof(len_m));
    p += sizeof(len_m);
    strcpy((char *) res + p, message);
    return res;
}

scp_message *decode_message(u8 *data) {
    // 解码scp_message
    // sender_name
    size_t p = 0;
    size_t len_sn = *(size_t *) data + p;
    p += sizeof(len_sn);
    char *sender_name = (char *) data + p;
    p += len_sn;
    // message
    size_t len_m = *(size_t *) data + p;
    p += sizeof(len_m);
    char *message = (char *) data + p;
    // 放入结构体
    scp_message *sd = (scp_message *) malloc(sizeof(scp_message));
    sd->message = message;
    sd->sender_name = sender_name;
    return sd;
}