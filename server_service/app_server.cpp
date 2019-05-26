

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
    _listener.support(methods::OPTIONS, std::bind(&AppServer::handleOptions, this, std::placeholders::_1));

}

void AppServer::handleGet(http_request message) {
    auto path = requestPath(message);
    http_response res;
    res.headers().add(U("Access-Control-Allow-Origin"), U("*"));

    if (!path.empty()) {
        if (path[0] == "auth") {
            auto response = json::value::object();
            response["version"] = json::value::string("0.0.1");
            res.set_status_code(status_codes::OK);
            res.set_body(response);
        }
        else if (path[0] == "service" && path[1] == "test") {
            auto response = json::value::object();
            response["version"] = json::value::string("0.0.1");
            response["status"] = json::value::string("ready!");
            res.set_status_code(status_codes::OK);
            res.set_body(response);
        }
        else if (path[0] == "tasks"  && path.size() == 2) {
            try{
                int id;
                std::istringstream iss (path[1]);
                iss >> id;

                TMApp::Task * task = app.tasks.getById(id);

                json::value obj = json::value::object();


                if (task != nullptr) {
                    obj = taskToJson(task);
                    res.set_status_code(status_codes::OK);
                } else {
                    obj["message"] = json::value::string("Task no found");
                    res.set_status_code(status_codes::NotFound);
                }
                res.set_body(obj);
            }catch(std::exception & e) {
                res.set_status_code(status_codes::BadRequest);
            }
            message.reply(res);
        }
        else if (path[0] == "tasks" && path.size() == 1) {
            int folderId = 1;
            auto query = uri::split_query(message.relative_uri().query());

            if (query.find("folderId") != query.end()) {
                auto q = query["folderId"];
                std::istringstream iss (q);
                iss >> folderId;
            }


            std::vector<TMApp::Task *> tasks = app.tasks.getByFolderId(folderId);

            if (query.find("sort") != query.end()) {
                std::sort(tasks.begin(), tasks.end());
            }

            auto response = json::value::object();
            json::value result = json::value::array();
            int i = 0;
            for(auto const& item: tasks) {
                json::value obj = json::value::object();
                obj = taskToJson(item);
                result[i++] = obj;
            }
            response["data"] = result;
            res.set_status_code(status_codes::OK);
            res.set_body(response);
        }
    }
    else {
        res.set_status_code(status_codes::NotFound);
    }
    message.reply(res);
}

void AppServer::handlePatch(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));
}

void AppServer::handlePut(http_request message) {
    auto path = requestPath(message);

    http_response res;
    res.headers().add(U("Access-Control-Allow-Origin"), U("*"));


    if (!path.empty()) {
        if (path[0] == "tasks" && path.size() == 2) {
            message
                .extract_json().then([=](json::value request) {
                    http_response response;
                    response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
                    try{
                        int taskId;
                        std::istringstream iss (path[1]);
                        iss >> taskId;

                        auto task = jsonToTask(request);
                        app.tasks.update(&task);

                        response.set_status_code(status_codes::OK);
                        response.set_body(taskToJson(&task));
                    }catch(std::exception & e) {
                        response.set_status_code(status_codes::BadRequest);
                    }
                    message.reply(response);
                });
        } else {
            res.set_status_code(status_codes::BadRequest);
            message.reply(res);
        }
    } else {
        message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
    }}

void AppServer::handlePost(http_request message) {
    auto path = requestPath(message);

    http_response res;
    res.headers().add(U("Access-Control-Allow-Origin"), U("*"));

    if (!path.empty()) {
        if (path[0] == "auth") {
            auto response = json::value::object();
            response["id"] = json::value::string("1");
            response["uid"] = json::value::string("a@mail.ru");
            response["email"] = json::value::string("a@mail.ru");
            response["provider"] = json::value::string("email");
            res.set_status_code(status_codes::OK);
            res.set_body(response);

            res.headers().add(U("uid"), U("a@mail.ru"));
            res.headers().add(U("access-token"), U("fake-access-token"));
            res.headers().add(U("client"), U("fake-client-id"));
            res.headers().add(U("token-type"), U("Bearer"));
            res.headers().add(U("expiry"), U("1558732245"));

            message.reply(res);
        }
        else if (path[0] == "tasks" &&
            path[1] == "create") {

            message.
                    extract_json().
                    then([=](json::value request) {
                http_response res;
                res.headers().add(U("Access-Control-Allow-Origin"), U("*"));
                try {
                    TMApp::Task* task = new TMApp::Task(request.at("title").as_string(), 1);

                    app.tasks.add(1,task);

                    json::value obj = json::value::object();
                    obj["message"] = json::value::string(
                            "succesful created task!");
                    obj = taskToJson(task);

                    res.set_status_code(status_codes::OK);
                    res.set_body(obj);
                }
                catch(json::json_exception & e) {
                    res.set_status_code(status_codes::BadRequest);
                }
                message.reply(res);
            });
        }
    } else {
        res.set_status_code(status_codes::NotFound);
        message.reply(res);
    }
}

void AppServer::handleDelete(http_request message) {
    auto path = requestPath(message);

    http_response res;
    res.headers().add(U("Access-Control-Allow-Origin"), U("*"));


    if (!path.empty()) {
        if (path[0] == "tasks" && path.size() >= 2) {
            message
                  .extract_json().then([=](json::value request) {
                    http_response response;
                    response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
                    try{
                        int taskId;
                        std::istringstream iss (path[1]);
                        iss >> taskId;

                        app.tasks.remove(taskId);

                        response.set_status_code(status_codes::OK);
                    }catch(std::exception & e) {
                        response.set_status_code(status_codes::BadRequest);
                    }
                    message.reply(response);
                });
        } else {
            res.set_status_code(status_codes::BadRequest);
            message.reply(res);
        }
    } else {
        message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
    }
}

void AppServer::handleHead(http_request message) {
    message.reply(status_codes::NotImplemented, responseNotImpl(methods::HEAD));
}

void AppServer::handleOptions(http_request message) {
    http_response res;
    res.headers().add(U("Access-Control-Allow-Origin"), U("*"));
    res.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, PUT, DELETE, OPTIONS"));
    res.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With"));
    res.headers().add(U("Access-Control-Expose-Headers"), U("access-token, expiry, token-type, uid, client"));
    auto path = requestPath(message);

    if (!path.empty()) {
        res.set_status_code(status_codes::OK);
    } else {
        res.set_status_code(status_codes::NotImplemented);
        res.set_body(responseNotImpl(methods::OPTIONS));
    }

    message.reply(res);
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

web::json::value AppServer::taskToJson(TMApp::Task * task) {
    json::value obj = json::value::object();
    obj["id"] = json::value::string(std::to_string(task->id));
    obj["title"] = json::value::string(task->title);
    obj["folderId"] = json::value::string(std::to_string(task->folderId));
    obj["done"] = json::value::boolean(task->completed);
    obj["priority"] = json::value::string(std::to_string(task->priority));
    obj["deadline-to-br"] = json::value::string(task->dueDate);
    obj["description"] = json::value::string(task->description);
    obj["actualTimeSpent"] = json::value::string(task->actualTimeSpent);
    obj["assignee"] = json::value::string(task->assignee);
    obj["estimatedTime"] = json::value::string(task->estimatedTime);
    obj["geoPlace"] = json::value::string(task->geoPlace);
    return obj;
}


TMApp::Task AppServer::jsonToTask(web::json::value &json){
    TMApp::Task task(json.at("title").as_string(), 1);
    std::istringstream iss (json.at("id").as_string());
    iss >> task.id;
    task.description = json.at("description").as_string();
    task.dueDate =  json.at("deadline").as_string();
    if (json.at("done").is_boolean()){
        task.completed =  json.at("done").as_bool();
    }

    return task;
}