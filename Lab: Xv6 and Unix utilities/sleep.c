#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    // 检查参数个数
    if (argc != 2) {
        fprintf(2, "Usage: sleep <ticks>\n");
        exit(1);
    }
    
    // 将字符串参数转换为整数
    int ticks = atoi(argv[1]);
    
    // 检查参数是否合法（正数）
    if (ticks < 0) {
        fprintf(2, "sleep: invalid argument\n");
        exit(1);
    }
    
    // 调用 pause() 系统调用等待指定的滴答数
    pause(ticks);
    
    // 正常退出
    exit(0);
}
