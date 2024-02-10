#ifndef __ERROR_H__
#define __ERROR_H__

#include <string>
#include <vector>
#include <cstdio>

#include "definitions.h"

struct Error
{
    int status;
    std::string message;
    std::string filename;
    int line;
    std::vector<std::string> stack;
};

#endif // __ERROR_H__