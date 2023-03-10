#ifndef SCP_H
#define SCP_H

#include "../utils/common.h"

typedef struct scp_header {
    u8  version;    // 版本
    u8  type;       // 类型
    u16 len;        // 数据长度
    u32 send_time;  // 发送时间
    u16 status;     // 状态
} scp_header;

typedef struct scp_message {
    char *sender_name;  // 发送人名称
    char *message;      // 发送信息
} scp_message;

u8 *pack_scp(u8 *, u16 *);

u8 *unpack_scp(u8 *);

u8 *encode_message(scp_message *, u16 *);

scp_message *decode_message(u8 *);

#endif //SCP_H