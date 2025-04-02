#include "log.h"

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


void logger(int level, const char *message, ...) {
    va_list args;  // 用于处理变长参数
    va_start(args, message);  // 初始化 args，message 是最后一个已知参数

    // 打印日志级别
    switch (level) {
        case LOG_ERROR:
            fprintf(stderr, "[error]: ");
            break;
        case LOG_INFO:
            fprintf(stderr, "[info]: ");
            break;
        case LOG_WARNING:
            fprintf(stderr, "[warn]: ");
            break;
        default:
            fprintf(stderr, "[info]: ");
            break;
    }

    // 打印格式化消息
    vfprintf(stderr, message, args);

    // 如果日志级别是错误，打印换行符
    if (level == LOG_ERROR) {
        fprintf(stderr, "\n");
    }

    va_end(args);  // 结束变长参数的处理
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