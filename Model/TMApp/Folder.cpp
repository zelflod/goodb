/**
 * Project OrganizeMe
 */


#include "Folder.h"

/**
 * Folder implementation
 */

namespace TMApp {
    /**
     * @param name
     */
    void Folder::SetName(std::string name) {
        this->name = name;
    }

    Folder::Folder() {}
    /**
     * @param name
     */
    Folder::Folder(std::string name) {
        this->name = name;
    }

    Folder::Folder(CoreApp *_app): app(_app){
    }

    Folder *Folder::getById(int folderId) {
        this->app->getRepository()->getFolderById(folderId);
    }

    void Folder::update(Folder *pFolder) {
        this->app->getRepository()->updateFolder(pFolder);
    }

    void Folder::add(Folder *pFolder, int projectId) {
        this->app->getRepository()->insertFolder(pFolder, projectId);
    }

    void Folder::remove(Folder *pFolder, int projectId) {
        this->app->getRepository()->removeFolder(pFolder, projectId);
    }

    std::vector<Folder *> Folder::getByProjectId(int projectId) {\
        return this->app->getRepository()->getFoldersByProjectId(projectId);
    }

    void Folder::attachApp(CoreApp* _app){
        this->app = _app;
    }
}


