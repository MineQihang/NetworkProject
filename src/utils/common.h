#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char  u8;   // Byte
typedef unsigned short u16;  // 2Byte
typedef unsigned int   u32;  // 4Byte
static u8 show_proc = 1;     // 为 0 时不打印中间结果

static void print_hex(u8* data, const u16 len, const char* str) {
    printf("======== %s ========", str);
    for(int i = 0; i < len; i ++ ){
        if(i % 8 == 0) printf("\n");
        printf("0x%02X ", data[i]);
    }
    printf("\n\n");
}

#endif //COMMON_H