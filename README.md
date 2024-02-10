# The Middleware Pattern

---

In the world of web development, there's a crucial concept called the Middleware Pattern. It's like the conductor in an orchestra, directing each musician to play their part at the right time.

## Overview

---

### **What is Middleware?**

I think the best technical definition of what a middleware is (in context of web development) that I've ever read was from a document on a [Microsoft ASP.NET docs website](https://learn.microsoft.com/en-us/aspnet/core/fundamentals/middleware/?view=aspnetcore-8.0&tabs=aspnetcore2x):

> Middleware is software that's assembled into an app pipeline to handle requests and responses. Each component:
> 
> - Chooses whether to pass the request to the next component in the pipeline.
> - Can perform work before and after the next component in the pipeline.

Middleware is a piece of software that helps handle requests and responses in a web application. Think of it as a gatekeeper that checks each request and decides what to do with it next. It's like a traffic cop directing cars at an intersection.

### **How Does it Work?**

When a request comes into a web application, it passes through a series of middleware components. Each component can perform tasks like checking for authentication, logging, or modifying the request before passing it on to the next component. It's like a relay race, where each runner (middleware) does their part before passing the baton (request) to the next runner.

### **Why is it Important?**

The Middleware Pattern helps keep our code organized and modular. Instead of having one big chunk of code to handle every request, we can break it down into smaller, reusable pieces. It's like building with LEGO bricks – we can mix and match different pieces to create something new each time.

## Important Points

---

Before we dive into the nitty-gritty of the code, let's quickly brush up on some important concepts that it relies on:

### 1. **`<functional>`**: Powering Up Your Functions

This library is a Swiss Army knife for function manipulation. It's like having a toolbox full of gadgets to tweak, transform, and tinker with your functions. From function pointers to functors and lambdas, **`<functional>`** brings versatility to your code, allowing you to pass functions around like hot potatoes.

### 2. **`<exception>`**: Handling Errors Like a Pro

Errors happen, and when they do, we need to handle them gracefully. Enter **`<exception>`**, the safety net for our code. I am fully aware of the debate around the terribleness of exceptions - I will just ignore it (for now) until I or someone else can suggest a better way to handle errors in this context.
I will use these stuff - make sure to read their documentation to see how they work: [`std::exception_ptr`](https://en.cppreference.com/w/cpp/error/exception_ptr), [`std::rethrow_exception`](https://en.cppreference.com/w/cpp/error/rethrow_exception), and [`std::current_exception`](https://en.cppreference.com/w/cpp/error/current_exception).

### 3. Recursive Function Calls: Going Down the Rabbit Hole

Sometimes, the best way to solve a problem is by diving deeper into it. That's where recursive function calls come in handy. These bad boys allow a function to call itself, opening up a world of possibilities for tackling complex problems. It's like going down a never-ending rabbit hole of computation – each recursion peeling back another layer of the problem until we reach the solution.

With these concepts under our belt, we're armed and ready to tackle the code.

## Exploring The Code

---

The main idea is that a pair of incoming message and outgoing message objects will recurse through a stack of function calls stored in an `std::vector` within a central object `Application` which orchestrate the pattern.

The user will mount middleware functions via `Application::mount` which will create an `MLayer` object that stores `path`, `handle_req` and `handle_err` .The path will be initialized as `*` for application-level middleware functions, otherwise, it will store the address of route-level middleware functions. It will store a value for `handle_req` if the function is a middleware, otherwise, it will store a value for `handle_err` if the function is an error handler, and the other member will be `nullptr`. 

In **`[definitions.h](https://github.com/zaki-x86/middleware-pattern-example/blob/main/definitions.h)` - I** declared some types that are used all over the place:

- Declaration of `InMessage` is a simple POD that stores information coming from network socket or whatever entity that sends messages.
- Declaration of `OutMessage` is a bit more than a POD - it is a struct which keeps public members to store system response to an incoming message. It introduces a `send` function - which simulates some kind of network action of sending data however in reality all it does is that it changes a `boolean` member variable `response_sent` to true - such that any object who is interested would know that this message has already been delivered.

> Both `InMessage` and `OutMessage` are defined in `[messages.h](https://github.com/zaki-x86/middleware-pattern-example/blob/main/messages.h)`
> 
- `Next` is a function type - which takes a pointer to exception as argument. This type will be of the 3rd argument of the middleware function handler.
- `Handler` is also a function type - which takes 3 arguments and is basically the signature of any middleware component that intercepts and an incoming message and write an out message.
- `ErrorHandler` is a function type of the error handler middleware functions - takes 4 arguments instead of 3 and is automatically passed control when an error occurs.
- `QERR` is a convenience macro which is just a function call `current_exception()` which returns an exception pointer to the currently raised exception.

`Application` is the class that where out middleware pattern resides. As illustrated above `mount` and its overloads are used to create layers and store them in `m_Stack<MLayer*>` - it also stores the index of the current middleware being executing. All the magic happens in the `next` function which is documented with printed messages and comments.
