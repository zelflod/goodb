
#pragma once

#include <string>
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>
#include "http_server.hpp"

using namespace web;
using namespace http::experimental::listener;

namespace cfx {
    class BasicServer {
    protected:
        http_listener _listener;

    public:
        BasicServer();
        ~BasicServer();

        void setEndpoint(const std::string & value);
        std::string endpoint() const;
        pplx::task<void> accept();
        pplx::task<void> shutdown();

        virtual void initRestOpHandlers() { 
            /* had to be implemented by the child class */ 
        }

        std::vector<utility::string_t> requestPath(const http_request & message);
    };
}