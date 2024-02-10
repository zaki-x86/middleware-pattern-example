# The Middleware Pattern

I think the best technical definition of what a middleware is (in context of web development) that I've ever read was from a document on a [Microsoft ASP.NET docs website](https://learn.microsoft.com/en-us/aspnet/core/fundamentals/middleware/?view=aspnetcore-8.0&tabs=aspnetcore2x):

> Middleware is software that's assembled into an app pipeline to handle requests and responses. Each component:
>
>- Chooses whether to pass the request to the next component in the pipeline.
>- Can perform work before and after the next component in the pipeline.

Ever wonder how your package gets from one place to another? Let’s peek into the post office.

**Middleware as a Parcel Sorter:**

When you drop off your package, it goes through a series of conveyor belts and sorting machines.
These machines act as middleware, directing each parcel to the right destination based on its address.
Without this middleware, your package might end up in Timbuktu instead of Tokyo.

Middleware are obviously used in context where messages needs to be exchanged between 2 parties. The incoming message goes through a chain of middleware components, and each component process the message and decide whether to pass it to the next processor or send back a response.

The middleware pattern is often used as a way to describe how message routing is handled in a microservices system.

## The example in this repo

We will have a central authority object that routes messages to their appropriate middleware handler based on the address of the incoming message.

There are two types of middleware components:

- App-level middleware: they operate on each incoming message regardless of the address.
- Address-level middleware: they operate on messages with the specific address which they are mapped to.
- Error-handler middleware: they have a different signature than the above middlewares as they accept an extra argument which is the `Error` object - this object is gonna store information about anything that goes wrong.

If you've ever worked with ExpressJS. This repository will help you understand how its middleware system works under the hood!

**So, how our middleware component looks like?**

The middleware should be just a function (whether it is an app-level or address-level) that accepts 3 arguments: `InMessge`, `OutMessage`, `Error` objects. It will process the incoming object, and set values in the outgoing message as needed or modify any application state as needed depending on the type of the middleware and how it is defined. The error handler middleware will accept 4 arguments instead.
