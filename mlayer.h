#ifndef __MLAYER_H__
#define __MLAYER_H__

#include <map>
#include <string>

#include "definitions.h"

struct MLayer
{
    std::string path = "*";
    Handler handle_req = nullptr;
    ErrorHandler handle_err = nullptr;
};


#endif // __MLAYER_H__