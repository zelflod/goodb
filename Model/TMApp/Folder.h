/**
 * Project OrganizeMe
 */


#ifndef _FOLDER_H
#define _FOLDER_H

#include <string>
#include <vector>
#include "CoreApp.h"

namespace TMApp {

    class Folder {
    public:
        std::string name;
        int projectId;
        int id;

        Folder();

        Folder(CoreApp* app);

        /**
         * @param name
         */
        void SetName(std::string name);

        /**
         * @param name
         */
        Folder(std::string name);

        void attachApp(CoreApp* app);

        std::vector<Folder *> getByProjectId(int projectId);

        Folder *getById(int i);

        void update(Folder *pFolder);

        void add(Folder *pFolder, int i);

        void remove(Folder *pFolder, int i);

    private:
        CoreApp * app;
    };

}


#endif