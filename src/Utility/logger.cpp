
#include "logger.h"


using namespace util;

void Logger::Log(const std::string& message, LoggerStatus logStatus) {

    std::cout << getHeader(logStatus) << message << std::endl;

}

const std::string& Logger::getHeader(LoggerStatus logStatus) {

    switch(logStatus){

        case LoggerStatus::INFO:
            return INFOHeader;
        case LoggerStatus::WARNING:
            return WARNINGHeader;
        case LoggerStatus::ERROR:
            return ERRORHeader;
        default:
            return INFOHeader;
    }

}
