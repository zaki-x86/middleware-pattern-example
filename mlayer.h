#ifndef __MLAYER_H__
#define __MLAYER_H__

#include <map>
#include <string>

#include "definitions.h"

struct MLayer
{
    MLayer(std::string path, Handler handle_req);
    MLayer(std::string path, ErrorHandler handle_err);
    std::string path;
    Handler handle_req;
    ErrorHandler handle_err;
};


#endif // __MLAYER_H__