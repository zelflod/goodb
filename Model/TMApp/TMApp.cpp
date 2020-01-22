

#include "TMApp.h"

namespace TMApp {

    TMApp::TMApp() {
    }

    TMApp::TMApp(Repository* _repository, Folder& f, Task& t,Project& p, Tag& _tags):
        repository(_repository),
        folders(f),
        projects(p),
        tasks(t),
        tags(_tags){}

    bool TMApp::signup(std::string username, std::string password) {
        this->_user->SetUsername(username);
        this->_user->Create();
        this->_user->SetPassword(password);
    }

    bool TMApp::login(std::string username, std::string password) {
        this->_user->SetUsername(username);
        this->loggedIn = this->_user->VerifyPassword(password);
        return this->loggedIn;
    }

    void TMApp::attachRepository(Repository* repository) {
        this->repository = repository;
    }

    User* TMApp::getUser() {
        return this->_user;
    }

    bool TMApp::isLoggedIn() {
        return this->loggedIn;
    }

    void TMApp::init(){
        this->_user = new User();
        this->_user->attachApp(this);

        Project p(this);
        this->projects = p;
        Tag t(this);
        this->tags = t;
        Folder f(this);
        this->folders = f;
        Task _tasks(this);
        this->tasks= _tasks;

    }

    Repository* TMApp::getRepository() {
        return this->repository;
    }

    std::string& TMApp::getUsername(){
        return this->_user->getUsername();
    }
}
