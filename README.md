# Proxygen routing: Internal request router for Facebook's HTTP server

This project implements a request routing system for
[Proxygen HTTP server](https://github.com/facebook/proxygen).
It's using [libr3](https://github.com/c9s/r3) to match incoming HTTP request to `proxygen::RequestHandler`.
If route is not found it returns a default handler: _404 - Not Found_.

## Usage

```cpp
std::vector<std::shared_ptr<AbstractRoute>> routes = {
	std::make_shared<Route<MyRouteHandler>>("/example", HTTPMethod::GET),
	std::make_shared<Route<HelloHandler>>("/hello/{test}", HTTPMethod::GET)
};

HTTPServerOptions options;
options.handlerFactories = RequestHandlerChain()
	.addThen<Router>(routes)
	.build();
```


## Build and install
The whole build process is not down but you might try the following:

```
autoreconf -ivf
./configure
make
make install
```

## Credits
The original idea comes from
[proxygen-tileserver](https://github.com/Goos/proxygen-tileserver/)
 (developed by [Goos](https://github.com/Goos)). I reimplemented this idea with
C++ templates, inheritance, etc.

# License
Apache-2.0 - Copyright 2016 Raphael Medaer <rme@escaux.com>
