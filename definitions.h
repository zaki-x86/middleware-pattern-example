#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#include <functional>

struct InMessage;
struct OutMessage;

using Next = std::function<void(std::exception_ptr)>;
using Handler = std::function<void(InMessage&, OutMessage&, Next)>;
using ErrorHandler = std::function<void(std::exception_ptr, InMessage&, OutMessage&, Next)>;

// ---- globals ----
#define QERR std::current_exception()

#endif // __DEFINITIONS_H__