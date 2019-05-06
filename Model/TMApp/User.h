/**
 * Project OrganizeMe
 */


#ifndef _USER_H
#define _USER_H

#include <string>
#include "MutuallyAttachable.h"
#include "CoreApp.h"

namespace TMApp {

    class User : MutuallyAttachable{
    public:
        User();
        /**
         * @param username
         */
        User(std::string username);

        bool Create();

        /**
         * @param password
         */
        bool SetPassword(std::string password);

        void SetUsername(std::string newUsername);

        std::string& getUsername();

        /**
         * @param password
         */
        bool VerifyPassword(std::string password);

        void attachApp(CoreApp * app);

        bool hasDataAccess();

        ~User();

    private:
        std::string username;
        std::string hashedPassword;
        CoreApp * app = nullptr;
    };

}

#endif
