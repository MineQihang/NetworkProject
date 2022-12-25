#include "scp.h"

u8* pack_scp(u8* _) {
    // 封装SCP数据报
    return _;
}

u8* unpack_scp(u8* _) {
    // 解封装SCP数据报
    return _;
}

u8* encode_message(scp_message* sm) {
    // 编码message
    char* message = sm->message;
    char* sender_name = sm->sender_name;

    printf("message: %s\n", message);
    printf("sender_name: %s\n", sender_name);

    u8 len_m  = strlen(message);
    u8 len_sn = strlen(sender_name);

    printf("length of message: %hhu\n", len_m);
    printf("length of sender_name: %hhu\n", len_sn);

    u8* res = (u8*) malloc(len_m + len_sn + 2);
    memcpy(res, &len_m, 1);
    strcpy((char *)res + 1, message);
    strcpy((char *)res + len_m + 1, sender_name);
    return res;
}

scp_message* decode_message(u8* data) {
    // 解码message
    u8 len_m = *data;
    printf("length of message: %hhu\n", len_m);

    u8 len_data = strlen((char*)data + 1);
    printf("length of data: %hhu\n", len_data);
    u8 len_sn = len_data - len_m;
    printf("length of sender_name: %hhu\n", len_sn);

    char* message = (char*) malloc(len_m + 1);
    memcpy(message, data + 1, len_m);
    message[len_m] = '\0';
    char* sender_name = (char*) malloc(len_sn + 1);
    memcpy(sender_name, data + 1 + len_m, len_sn);

    scp_message* sd = (scp_message*) malloc(sizeof(scp_datagram));
    sd->message = message;
    sd->sender_name = sender_name;

    return sd;
}