
#include <iostream>

#include <usr_interrupt_handler.hpp>
#include <runtime_utils.hpp>

#include "app_server.hpp"

using namespace web;
using namespace cfx;

int main(int argc, const char * argv[]) {
    InterruptHandler::hookSIGINT();

    std::string address = "host_auto_ip4";
    std::string port = "9090";
    if (argc >= 3) {
        address = argv[1];
        port = argv[2];
    }

    AppServer server;
//    server.setEndpoint("http://host_auto_ip4:9090/api");
    std::string endpoint = "http://" + address + ":"+ port +"/api";
    server.setEndpoint(endpoint);


    try {
        // wait for server initialization...
        server.accept().wait();
        std::cout << "TMApp Server now listening for requests at: " << server.endpoint() << '\n';
        
        InterruptHandler::waitForUserInterrupt();

        server.shutdown().wait();
    }
    catch(std::exception & e) {
        std::cerr << "что-то пошло не так! :(" << '\n';
    }
    catch(...) {
        RuntimeUtils::printStackTrace();
    }

    return 0;
}
