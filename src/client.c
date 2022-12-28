#include "procedure/pack.h"
#include "procedure/unpack.h"
#include <pthread.h>

char sender_name[255]; // 发送人名称

int send_message(const char *message) {
    // 发送信息
    // 封装
    scp_message msg = {
            .sender_name = sender_name,
            .message     = message
    };
    u16 *len = malloc(sizeof(u16));
    u8 *data = pack(&msg, len);
    // 打开文件
    FILE *fout;
    if ((fout = fopen("./data", "wb")) == NULL) return -1;
    // printf("0x%X\n", *data);
    // 写入文件
    // printf("len: %d\n", *len);
    for (int i = 0; i < *len; i++)
        fwrite(data + i, sizeof(u8), 1, fout);
    fclose(fout);
    return 1;
}

int receive_message() {
    // 接收信息
    // 打开文件
    FILE *fin;
    if ((fin = fopen("./data", "rb")) == NULL) return -1;
    // 读文件
    fseek(fin, 0, SEEK_END);
//    printf("%ld", ftell(fin));
    int len = ftell(fin) / sizeof(u8);
    if (len <= 0) return -1;
    rewind(fin);
//    printf("%d\n", len);
    u8 *data = (u8 *) malloc(len * sizeof(u8));
    fread(data, sizeof(u8), len, fin);
    fclose(fin);
    // 解封装
//    printf("0x%X\n", *(data + 2));
    scp_message *rec = unpack(data);
    if(rec == NULL) return 1;
//    printf("sender_name: %s\n", rec->sender_name);
//    printf("message: %s\n", rec->message);
    if(strcmp(rec->sender_name, sender_name) == 0) return 0;
    else {
        printf("[%s]:%s\n", rec->sender_name, rec->message);
        while(remove("./data") != 0);
        return 1;
    }
}

void flag_write() {
    FILE *f;
    while((f = fopen("./writing", "wb")) == NULL);
    fclose(f);
}

void cancel_flag_write() {
    remove("./writing");
}

int is_flag_write() {
    FILE *f;
    if((f = fopen("./writing", "rb")) == NULL) return 1;
    fclose(f);
    return 0;
}

void *send() {
    while(1) {
        char message[255];
        if(gets(message) != NULL) {
            while(strlen(message) <= 0) gets(message);  //获取用户输入
            flag_write();     // 写信号
            printf("[%s]:%s\n", sender_name, message);
            while (send_message(message) <= 0);    // 封装并发送
            cancel_flag_write();   // 关闭写信号
        }
    }
}

void *receive() {
    while (1) {
        if(!is_flag_write()) continue;
        if(receive_message() > 0) while(remove("./data") != 0);
    }
}

int main() {
    printf("Your name:");
    scanf("%s", sender_name);

    pthread_t sender;     // 发送线程
    pthread_t receiver;   // 接收线程
    pthread_create(&sender, NULL, send, NULL);
    pthread_create(&receiver, NULL, receive, NULL);
    pthread_join(sender, NULL);
    pthread_join(receiver, NULL);
    return 0;
}