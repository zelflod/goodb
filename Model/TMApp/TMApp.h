
#ifndef GOODB_TMAPP_H
#define GOODB_TMAPP_H


#include "CoreApp.h"
#include <string>
#include "User.h"
#include "Project.h"
#include "Tag.h"
#include "Folder.h"
#include "Task.h"



namespace TMApp{

    class TMApp : public CoreApp {
    public:
        TMApp();
        ~TMApp(){};

        TMApp(Repository* _repository, Folder& f, Task& t,Project& p, Tag& _tags);

        void attachRepository(Repository* repository);

        bool login(std::string username, std::string password);

        bool signup(std::string username, std::string password);

        bool isLoggedIn();

        User* getUser();

        void init();

        Repository* getRepository();
        std::string& getUsername();

        Project projects;
        Tag tags;
        Folder folders;
        Task tasks;

    private:
        User* _user;
        bool loggedIn = false;
        Repository* repository;
    };
}


#endif
