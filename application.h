#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <cstdio>
#include <vector>

#include "definitions.h"
#include "Error.h"
#include "messages.h"
#include "mlayer.h"

struct Application {
    Application();

    void mount(Handler handler);
    void mount(ErrorHandler err_handler);
    void mount(std::string path, Handler handler);

    void handle(InMessage& in, OutMessage& out);

private:
    void next(InMessage& in, OutMessage& out, Error& err);

private:
    std::vector<MLayer *> m_Stack;
};

#endif // __APPLICATION_H__