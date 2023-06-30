#pragma once

#include <exception>
#include <cstdio>
#include <source_location>

#include <utility>
#include <ctime>

#define ERROE_MSG_BUFFER 512

class BaseError : public std::exception {
public:
    BaseError(
        const char *filename,
        const char *funcname,
        const int line,
        const char *time,
        const char *errortype) noexcept
    {
        snprintf(msg, sizeBuf,
                "\nIn file: %s, in function: %s, at line: %d, at: %s\nOccured: \033[31m%s\033[37m",
                filename, funcname, line, time, errortype);
    }

    virtual const char *what() const noexcept override{
        return msg;
    }
    
private:
    static constexpr size_t sizeBuf = ERROE_MSG_BUFFER;
    char msg[sizeBuf]{};
};