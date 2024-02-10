#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <string>
#include <map>

#include "definitions.h"

struct InMessage {
    std::string path;
    std::map<std::string, std::string> headers;
    std::string body;
};

struct OutMessage {
    int status;
    std::map<std::string, std::string> headers;
    std::string body;

    void send() {
        APP.response_sent = true;
    }

private:

};

#endif // __MESSAGES_H__