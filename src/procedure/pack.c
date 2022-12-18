#include "pack.h"

u8* pack(scp_datagram* sd){
    char* message = sd->message;
    char* sender_name = sd->sender_name;
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