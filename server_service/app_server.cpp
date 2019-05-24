

#include <std_htpp_server.hpp>
#include "app_server.hpp"
#include <tuple>



using namespace web;
using namespace http;

void AppServer::initRestOpHandlers() {
    _listener.support(methods::GET, std::bind(&AppServer::handleGet, this, std::placeholders::_1));
    _listener.support(methods::PUT, std::bind(&AppServer::handlePut, this, std::placeholders::_1));
    _listener.support(methods::POST, std::bind(&AppServer::handlePost, this, std::placeholders::_1));
    _listener.support(methods::DEL, std::bind(&AppServer::handleDelete, this, std::placeholders::_1));
    _listener.support(methods::PATCH, std::bind(&AppServer::handlePatch, this, std::placeholders::_1));
}

void AppServer::handleGet(http_request message) {
    auto path = requestPath(message);
    if (!path.empty()) {
        if (path[0] == "service" && path[1] == "test") {
            auto response = json::value::object();
            response["version"] = json::value::string("0.0.1");
            response["status"] = json::value::string("ready!");
            message.reply(status_codes::OK, response);
        }
        else if (path[0] == "task") {
            int id;
            std::istringstream iss (path[1]);
            iss >> id;
            TMApp::Task * task = app.tasks.getById(id);
            auto response = json::value::object();
            if (task != nullptr) {
                response["task"] = json::value::string(task->title);
                response["id"] = json::value::string(std::to_string(task->id));
                message.reply(status_codes::OK, response);
            } else {
                response["message"] = json::value::string("Task no found");
                message.reply(status_codes::OK, response);
            }
        }
        else if (path[0] == "tasks") {
            int folderId;
            std::istringstream iss (path[1]);
            iss >> folderId;
            std::vector<TMApp::Task *> tasks = app.tasks.getByFolderId(folderId);
            auto response = json::value::object();
            json::value result = json::value::array();
            int i = 0;
            for(auto const& item: tasks) {
                json::value obj = json::value::object();
                obj["id"] = json::value::string(std::to_string(item->id));
                obj["title"] = json::value::string(item->title);
                obj["folderId"] = json::value::string(std::to_string(item->folderId));
                obj["completed"] = json::value::string(std::to_string(item->completed));
                obj["priority"] = json::value::string(std::to_string(item->priority));
                obj["dueDate"] = json::value::string(item->dueDate);
                obj["description"] = json::value::string(item->description);
                obj["actualTimeSpent"] = json::value::string(item->actualTimeSpent);
                obj["assignee"] = json::value::string(item->assignee);
                obj["estimatedTime"] = json::value::string(item->estimatedTime);
                obj["geoPlace"] = json::value::string(item->geoPlace);
                result[i++] = obj;
            }
            response["tasks"] = result;
            message.reply(status_codes::OK, response);
        }
    }
    else {
        message.reply(status_codes::NotFound);
    }
}

void AppServer::handlePatch(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));
}

void AppServer::handlePut(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PUT));
}

void AppServer::handlePost(http_request message) {
    auto path = requestPath(message);

    if (!path.empty() &&
        path[0] == "task" &&
        path[1] == "create") {

        message.
                extract_json().
                then([=](json::value request) {
            try {
                app.tasks.add(10, new TMApp::Task(request.at("title").as_string()));

                json::value response;
                response["message"] = json::value::string(
                        "succesful created task!");
                message.reply(status_codes::OK, response);
            }
            catch(json::json_exception & e) {
                message.reply(status_codes::BadRequest);
            }
        });
    }
}

void AppServer::handleDelete(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
}

void AppServer::handleHead(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::HEAD));
}

void AppServer::handleOptions(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::OPTIONS));
}

void AppServer::handleTrace(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::TRCE));
}

void AppServer::handleConnect(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::CONNECT));
}

void AppServer::handleMerge(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::MERGE));
}

json::value AppServer::responseNotImpl(const http::method & method) {
    auto response = json::value::object();
    response["http_method"] = json::value::string(method);
    return response ;
}