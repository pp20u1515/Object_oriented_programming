#pragma once

#include "BaseError.h"

class IteratorError: public BaseError {
public:
    IteratorError (
        const char *filename,
        const char *funcname,
        const int line,
        const char *time,
        const char *errortype) noexcept
        : BaseError(filename, funcname, line, time, errortype)
    {}
};

class NotExpiredIteratorError : public IteratorError {
public:
    NotExpiredIteratorError(
        const char *filename,
        const char *funcname,
        const int line,
        const char *time,
        const char *errortype = "Pointer was expired!") noexcept
        : IteratorError(filename, funcname, line, time, errortype)
    {}
};

class OutOfRangeIteratorError : public IteratorError {
public:
    OutOfRangeIteratorError(
        const char *filename,
        const char *funcname,
        const int line,
        const char *time,
        const char *errortype = "Pointer access was out of range!") noexcept
        : IteratorError(filename, funcname, line, time, errortype)
    {}
};