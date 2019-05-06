/**
 * Project OrganizeMe
 */


#ifndef _TAG_H
#define _TAG_H

#include <string>
#include <vector>
#include "CoreApp.h"

namespace TMApp {

    class Tag {
    public:

        Tag();

        Tag(CoreApp* app);

        /**
         * @param name
         */
        Tag(std::string name);

        int projectId;

        std::string name;

        void attachApp(CoreApp* app);

        /**
         * @param project_id
        */
        void GetTagsByProjectId(int project_id);

        std::vector<Tag *> getByProjectId(int i);

        Tag *getByName(std::string str, int i);

        void SetName(std::string str);

        void update(const std::string& oldName, const std::string& newName, int projectId);

        bool add(Tag *pTag, int projectId);

        void remove(std::string str, int projectId);

        void remove(Tag *pTag, int projectId);


    private:
        CoreApp * app;
    };

}

#endif