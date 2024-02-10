#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <iostream>
#include <vector>

#include "definitions.h"
#include "messages.h"
#include "mlayer.h"

struct Application {
    Application();
    ~Application();

    void mount(Handler handler);
    void mount(ErrorHandler err_handler);
    void mount(std::string path, Handler handler);

    void handle(InMessage& in, OutMessage& out);

private:
    void next(InMessage& in, OutMessage& out, std::exception_ptr err);

private:
    std::vector<MLayer*> m_Stack;
    int index;
};

#endif // __APPLICATION_H__