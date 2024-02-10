#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#include <functional>

struct Error;
struct InMessage;
struct OutMessage;

using Next = std::function<void(Error*)>;
using Handler = std::function<void(InMessage&, OutMessage&, Next)>;
using ErrorHandler = std::function<void(Error&, InMessage&, OutMessage&, Next)>;

// ---- globals ----

struct AppStatus {
    bool response_sent;
    Error* err;
};

extern AppStatus APP;

#endif // __DEFINITIONS_H__