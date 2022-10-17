
#ifndef BLOCKRPG_LOGGER_H
#define BLOCKRPG_LOGGER_H

#include <iostream>


namespace util{

    //different log status
    enum class LoggerStatus{
        INFO,
        WARNING,
        ERROR,
    };

    //Logging class to bring warnings/errors/test to console
    class Logger {
    public:
        //write message to console
        static void Log(const std::string& message, LoggerStatus logStatus = LoggerStatus::INFO);

        //get correct warning label
        static const std::string& getHeader(LoggerStatus logStatus);

        //static const variables can only be initialized in the header if inlined
        inline const static std::string INFOHeader      {"[INFO]: "};
        inline const static std::string WARNINGHeader   {"[WARNING]: "};
        inline const static std::string ERRORHeader     {"[ERROR]: "};

    };

}



#endif //BLOCKRPG_LOGGER_H
