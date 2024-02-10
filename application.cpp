#include "application.h"

Application::Application()
    : m_Stack()
{
    
}

Application::~Application()
{
    for (auto& layer : m_Stack) {
        delete layer;
    }
}

void Application::mount(Handler handler)
{
    auto layer = new MLayer;
    layer->handle_req = handler;
    m_Stack.push_back(layer);
}

void Application::mount(ErrorHandler err_handler)
{
    auto layer = new MLayer;
    layer->handle_err = err_handler;
    m_Stack.push_back(layer);
}

void Application::mount(std::string path, Handler handler)
{
    auto layer = new MLayer;
    layer->handle_req = handler;
    layer->path = path;
    m_Stack.push_back(layer);
}

void Application::handle(InMessage& in, OutMessage& out)
{
    std::cout << "Application::handle() called\n";

    index = 0;
    try {
        next(in, out, 0);
    }
    catch(const std::exception& e) {
        // your built-in error handler should be invoked here!
        std::cout << "application handler invokes final handler\n";
        std::cerr << e.what() << '\n';
    }
}

void Application::next(InMessage& in, OutMessage& out, std::exception_ptr err)
{
    if(m_Stack.size() == 0) {
        std::cerr << "Internal log: no middleware defined - skipping!\n";
        return;
    }

    else if (out.response_sent) {
        std::cerr << "Internal log: response already sent - skipping!\n";
        return;
    }

    else if (index < m_Stack.size()){
        auto layer = m_Stack[index];
        index++;

        if(err && layer->handle_err) {
            std::cout << "Internal log: app-level error handler middleware is called!\n";
            try {
                std::rethrow_exception(err);
            }
            catch(const std::exception& e) {
                std::cout << "Error desc: " <<  e.what() << "\n";
                layer->handle_err(err, in, out, [&in, &out, this](std::exception_ptr err){
                next(in, out, err);
            });
            }
        } else if(err && !layer->handle_err) {
            std::cout << "Internal log: error detected - checking for an error handler!\n";
            next(in, out, err);
        } else if (layer->path == "*"){
            std::cout << "Internal log: app-level middleware is called!\n";
            layer->handle_req(in, out, [&in, &out, this](std::exception_ptr err){
                next(in, out, err);
            });
        } else if (layer->path == in.path){
            std::cout << "Internal log: route-level middleware is called!\n";\
            layer->handle_req(in, out, [&in, &out, this](std::exception_ptr err){
                next(in, out, err);
            });
        } else if (layer->path == in.path && !layer->handle_req) {
            std::cout << "APP WARNING::Error:\n" << "CODE-404 - Not Found" << std::endl;
            next(in, out, err);
        }
            
    }

    // base case - in case no error handler defined by user or no response sent
    // if err exista and is not handled by the stack layer
    // our app should call a built-in error handler
    else if(err) {
        try {
            std::rethrow_exception(err);
        }
        catch(const std::exception& e) {
            std::cerr << "didn't find any error handlers!\n";
            std::cerr << e.what() << '\n';
            throw std::runtime_error("Unhandled err caught by built-in error handler!");
        }
    }

    if(out.response_sent == false) {
        std::cout << "404 - Not found\n";
        return;
    } else {
        return;
    }
    
}
