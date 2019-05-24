
#ifndef GOODB_COREAPP_H
#define GOODB_COREAPP_H

#include <string>
#include "Repository.h"

class CoreApp {
public:
    virtual std::string& getUsername() = 0;

    virtual Repository* getRepository() = 0;
};

#endif
