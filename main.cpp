#include <cstdio>
#include <string>

#include "application.h"

int main(int argc, char const *argv[])
{
    // --- Init app ---
    Application app{};

    // --- Mount middleware functions here ---
    app.mount([](InMessage& in, OutMessage &out, Next next) {
        printf("Middleware 1: %s\n", in.body.c_str());
        next(0);
    });

    app.mount([](InMessage& in, OutMessage &out, Next next) {
        printf("Middleware 2: %s\n", in.body.c_str());
        try {
            throw std::runtime_error("Something went wrong!");
            next(0);
        }
        catch(const std::exception& e) {
            std::cerr << "ERR in middleware2 passing to next error handler: " << e.what() << '\n';
            next(QERR);
        } 
    });

    app.mount([](std::exception_ptr err, InMessage& in, OutMessage &out, Next next) {
        printf("Error handler: ready to handler error received!\n");
        out = {500, {{"Content-Type", "text/plain"}}, "Internal Server Error!"};
        printf("returning response: %s\n", out.body.c_str());
        out.send();
    });

    app.mount([](InMessage& in, OutMessage &out, Next next) {
        auto name = in.headers.find("name") != in.headers.end() ? in.headers["name"] : "anonymous";
        out = {200, {{"Content-Type", "text/plain"}}, "Middleware 3: Hello " + name + "!"};
        printf("returning response: %s\n", out.body.c_str());
        out.send();
        next(0);
    });

    app.mount([](InMessage& in, OutMessage &out, Next next) {
        std::cout << "This middleware shouldn't be called!!!!\n";

        auto name = in.headers.find("name") != in.headers.end() ? in.headers["name"] : "anonymous";
        out = {200, {{"Content-Type", "text/plain"}}, "Middleware 3: Hello " + name + "!"};
        printf("returning response: %s\n", out.body.c_str());
        out.send();
    });

    // pretend as if you're listening for messages from a socket or something, and 
    // app will invoke the handle function automatically depending on the in message.

    InMessage in = {"/", {{"name", "client1"}, {"age", "50"}}, "Hello App!"};
    OutMessage out;
    app.handle(in, out);

    return 0;
}
