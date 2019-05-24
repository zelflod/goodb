
#pragma once 

#include <basic_server.hpp>
#include <Model/MockRepository.h>
#include <Model/TMApp/TMApp.h>

using namespace cfx;

class AppServer : public BasicServer, HttpServer {
public:
    AppServer() : BasicServer() {
        app.attachRepository(new MockRepository());
        app.init();
        std::string psw = "psw";
        if (!app.login("username", psw)) {
            app.signup("username", psw);
            app.login("username", psw);
        }
    };
    ~AppServer() {}
    void handleGet(http_request message) override;
    void handlePut(http_request message) override;
    void handlePost(http_request message) override;
    void handlePatch(http_request message) override;
    void handleDelete(http_request message) override;
    void handleHead(http_request message) override;
    void handleOptions(http_request message) override;
    void handleTrace(http_request message) override;
    void handleConnect(http_request message) override;
    void handleMerge(http_request message) override;
    void initRestOpHandlers() override;    

private:
    static json::value responseNotImpl(const http::method & method);
    TMApp::TMApp app;
};