
#include "basic_server.hpp"
#include "network_utils.hpp"

namespace cfx {
    BasicServer::BasicServer() {

    }

    BasicServer::~BasicServer() {

    }
    void BasicServer::setEndpoint(const std::string & value) {
        uri endpointURI(value);
        uri_builder endpointBuilder;

        endpointBuilder.set_scheme(endpointURI.scheme());
        if (endpointURI.host() == "host_auto_ip4") {
            endpointBuilder.set_host(NetworkUtils::hostIP4());        
        }
        else if (endpointURI.host() == "host_auto_ip6") {
            endpointBuilder.set_host(NetworkUtils::hostIP6());
        } else {
            endpointBuilder.set_host(endpointURI.host());
        }
        endpointBuilder.set_port(endpointURI.port());
        endpointBuilder.set_path(endpointURI.path());

        _listener = http_listener(endpointBuilder.to_uri());
    }

    std::string BasicServer::endpoint() const {
        return _listener.uri().to_string();
    }

    pplx::task<void> BasicServer::accept() {
        initRestOpHandlers();
        return _listener.open();
    }

    pplx::task<void> BasicServer::shutdown() {
        return _listener.close();
    }

    std::vector<utility::string_t> BasicServer::requestPath(const http_request & message) {
        auto relativePath = uri::decode(message.relative_uri().path());
        return uri::split_path(relativePath);        
    }
}