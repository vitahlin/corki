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

void loggerError(const char *message, ...) {
    va_list args;  // 用于处理变长参数
    va_start(args, message);  // 初始化 args，message 是最后一个已知参数

    // 打印日志级别
    fprintf(stderr, "[error]: ");

    // 打印格式化消息
    vfprintf(stderr, message, args);
    fprintf(stderr, "\n");

    va_end(args);  // 结束变长参数的处理
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