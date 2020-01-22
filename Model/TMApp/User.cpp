/**
 * Project OrganizeMe
 */


#include "User.h"
//#include "./../DBInterface/db.h"
#include "utils.h"

#define GET_VARIABLE_NAME(Variable) (#Variable)

/**
 * User implementation
 */

namespace TMApp {

    User::User() {
    }

    /**
     * @param username
     */
    User::User(std::string username) {
        this->username = username;
    }

    /**
     * @return bool
     */
    bool User::Create() {
        this->app->getRepository()->insertUser(this);
    }

    /**
     * @param password
     * @return bool
     */
    bool User::SetPassword(std::string password) {
        this->hashedPassword = TMApp::utils::sha256(password);
        this->app->getRepository()->updateUser(this);
        return true;
    }

    /**
     * @param password
     * @return bool
     */
    bool User::VerifyPassword(std::string password) {
        User* user = this->app->getRepository()->getUserByUsername(this->username);
        if (user == nullptr) {
            return false;
        }
        this->hashedPassword = TMApp::utils::sha256(password);
        if (user->hashedPassword.compare(this->hashedPassword) != 0) {
            return false;
        }
        return true;
    }

    void User::attachApp(CoreApp * app) {
        this->app = app;
    }

    void User::SetUsername(std::string newUsername){
        this->username = newUsername;
    }

    bool User::hasDataAccess() {
        if (this->app != nullptr && this->app->getRepository()){
            return true;
        }
        return false;
    }

    std::string& User::getUsername() {
        return this->username;
    }

    User::~User() {

    }

}
