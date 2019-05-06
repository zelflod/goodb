/**
 * Project OrganizeMe
 */


#include "Project.h"

/**
 * Project implementation
 */

namespace TMApp {
    /**
     * @param name
     */
    void Project::SetName(std::string name) {
        this->name = name;
    }

    Project::Project() {}
    Project::Project(CoreApp* _app): app(_app){
    }

    /**
     * @param name
     */
    Project::Project(std::string name) {

    }

    Project* Project::getDefault(){
        std::vector<Project *> projects = this->app->getRepository()->getProjectsByUserId(this->app->getUsername(), true);
        if (projects.empty()){
            return nullptr;
        }
        return projects[0];
    }

    void Project::setDefault(Project* project){
        project->name = "user_default";
        project->user = this->app->getUsername();
        project->is_default = true;
        this->app->getRepository()->insertProject(project);
    }

    std::vector<Project *> Project::getAll() {
        return this->app->getRepository()->getProjectsByUserId(this->app->getUsername(), false);
    }

    void Project::update(Project *&pProject) {
        this->app->getRepository()->updateProject(pProject);
    }

    void Project::attachApp(CoreApp* _app){
        this->app = _app;
    }

    void Project::setId(int _id) {
        id = _id;
    }

    int Project::getId() {
        return id;
    }

    void Project::setUserId(std::string& userId){
        user = userId;
    }

    std::string& Project::getUserId(){
        return user;
    }


}



