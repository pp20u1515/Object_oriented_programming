#pragma once

#include "BaseError.h"

class TreeError: public BaseError {
public:
    TreeError (
        const char *filename,
        const char *funcname,
        const int line,
        const char *time,
        const char *errortype
    ) noexcept : BaseError(filename, funcname, line, time, errortype) 
    {}
};

class TreeMemoryError: public TreeError {
public:
    TreeMemoryError (
        const char *filename,
        const char *funcname,
        const int line,
        const char *time,
        const char *errortype = "Cannot allocate memory for Node!"
    ) noexcept : TreeError(filename, funcname, line, time, errortype) 
    {}
};

class TreeInvalidRootError: public TreeError {
public:
    TreeInvalidRootError (
        const char *filename,
        const char *funcname,
        const int line,
        const char *time,
        const char *errortype = "Try to get tree from invalid root!"
    ) : TreeError(filename, funcname, line, time, errortype)
    {}
};