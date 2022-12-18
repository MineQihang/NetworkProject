#include "unpack.h"


scp_datagram* unpack(u8* data){
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

    scp_datagram* sd = (scp_datagram*) malloc(sizeof(scp_datagram));
    sd->message = message;
    sd->sender_name = sender_name;

    return sd;
}