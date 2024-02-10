#include "mlayer.h"

MLayer::MLayer(std::string path, Handler handle_req)
    : path(path), handle_req(handle_req)
{
    
}

MLayer::MLayer(std::string path, ErrorHandler handle_err)
    : path(path), handle_err(handle_err)
{
    
}