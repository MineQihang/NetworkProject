#include "procedure/pack.h"
#include "procedure/unpack.h"
#include <pthread.h>

int main() {
    scp_message msg = {
            "qihang",
            "Hello, world!"
    };

    u8* tmp = pack(&msg);

    scp_message* rec = unpack(tmp);

    printf("sender_name: %s\n", rec->sender_name);
    printf("message: %s\n", rec->message);

    return 0;
}