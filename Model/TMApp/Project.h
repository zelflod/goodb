/**
 * Project OrganizeMe
 */


#ifndef _PROJECT_H
#define _PROJECT_H

#include <string>
#include "MutuallyAttachable.h"
#include "CoreApp.h"

namespace TMApp {

    class Project : MutuallyAttachable  {
    public:
        Project();

        Project(CoreApp* app);

        Project(std::string name);

        std::string name;

        Project* getDefault();

        void setDefault(Project* project);

        void attachApp(CoreApp* app);

        /**
         * @param name
         */
        void SetName(std::string name);

        std::vector<Project *> getAll();

        void update(Project *&pProject);

        void setId(int id);

        int getId();

        void setUserId(std::string& userId);

        std::string& getUserId();

        bool is_default = false;
    private:
        int id = 0;
        std::string user;
        CoreApp * app;
    };


}
#endif