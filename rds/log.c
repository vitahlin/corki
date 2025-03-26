#include "log.h"
#include <stdio.h>
#include <time.h>

// 日志级别
int log_level = LOG_INFO;

// 获取当前时间的辅助函数
const char *current_time() {
    static char buffer[20];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    return buffer;
}

// 日志函数
void log_message(int level, const char *message) {
    if (level < log_level) {
        return;  // 如果日志级别低于设定的级别，就不输出
    }

    const char *level_str;
    switch (level) {
        case LOG_INFO:
            level_str = "INFO";
            break;
        case LOG_WARNING:
            level_str = "WARNING";
            break;
        case LOG_ERROR:
            level_str = "ERROR";
            break;
        default:
            level_str = "UNKNOWN";
            break;
    }

    printf("[%s] [%s] %s\n", current_time(), level_str, message);
}