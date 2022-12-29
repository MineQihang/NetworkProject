#include "scp.h"

void print_scp_header(scp_header* header) {
    printf("========== scp header ==========\n");
    printf("version: %d\n", header->version);
    printf("type: %d\n", header->type);
    printf("len: %d\n", header->len);
    printf("send_time: %d\n", header->len);
    printf("status: %d\n", header->status);
    printf("\n");
}

u8 *pack_scp(u8 *data, u16 *len) {
    // 封装SCP数据报
    scp_header header = {
            .version    =   1,
            .type       =   0,
            .len        =   *len,
            .send_time  =   32,
            .status     =   200
    };
    size_t header_size = sizeof(header);
    size_t data_size = *len;
    *len = (u16) header_size + data_size;
    u8 *packed_data = malloc(*len);
    memcpy(packed_data, &header, header_size);
    memcpy(packed_data + header_size, data, data_size);
    if(show_proc) print_scp_header(&header);
    return packed_data;
}

u8 *unpack_scp(u8 *data) {
    // 解封装SCP数据报
    scp_header header = *(scp_header *) data;
    size_t header_size = sizeof(header);
    // 打印SCP数据报
    if(show_proc) {
        print_hex(data, header.len + header_size, "unpack: scp datagram");
        print_scp_header(&header);
    }
    u8 *unpacked_data = data + header_size;
    return unpacked_data;
}

u8 *encode_message(scp_message *sm, u16 *len) {
    // 使用LV方式编码message
    char *sender_name = sm->sender_name;
    char *message = sm->message;

    size_t len_sn = strlen(sender_name) + 1;
    size_t len_m = strlen(message) + 1;

    *len = (u16) sizeof(len_sn) + len_sn + sizeof(len_m) + len_m;  // sizeof encoded message

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