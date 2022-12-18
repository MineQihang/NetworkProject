#include "procedure/pack.h"
#include "procedure/unpack.h"


int main() {
    // pack
    printf("packing...\n");
    scp_datagram send = {"hello", "qihang"};
    u8* res = pack(&send);
    printf("%llu\n", strlen((char*)res));

    // unpack
    printf("unpacking...\n");
    scp_datagram* receive = unpack(res);
    printf("sender_name: %s\n", receive->sender_name);
    printf("message: %s\n", receive->message);
    return 0;
}