#include "TimeUtils.h"
#include <chrono>

int TimeUtils::get_current_year() {
    const auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* local_tm = std::localtime(&now_c);
    return 1900 + local_tm->tm_year; 
}

int TimeUtils::get_current_month() {
    const auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* local_tm = std::localtime(&now_c);
    return local_tm->tm_mon + 1;      
}

int TimeUtils::get_current_day() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* local_tm = std::localtime(&now_c);
    return local_tm->tm_mday;    
}

int TimeUtils::get_current_day_of_week() {
    const auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* local_tm = std::localtime(&now_c);
    return local_tm->tm_wday;     
}