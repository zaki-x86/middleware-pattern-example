#include <cstdio>
#include <string>

#include "application.h"

AppStatus APP = {false, nullptr};

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
        next(0);
    });

    app.mount([](InMessage& in, OutMessage &out, Next next) {
        auto name = in.headers.find("name") != in.headers.end() ? in.headers["name"] : "anonymous";
        out = {200, {{"Content-Type", "text/plain"}}, "Middleware 3: Hello" + name + "!"};
        out.send();
    });

    // pretend as if you're listening for messages from a socket or something, and 
    // app will invoke the handle function automatically depending on the in message.

    InMessage in = {"/", {{"name", "client1"}, {"age", "50"}}, "Hello App!"};
    OutMessage out;
    app.handle(in, out);

    return 0;
}
