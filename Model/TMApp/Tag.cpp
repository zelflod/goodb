/**
 * Project OrganizeMe
 */


#include "Tag.h"

/**
 * Tag implementation
 */


namespace TMApp {
    Tag::Tag() {
    }
    Tag::Tag(CoreApp* _app): app(_app){
    }

    /**
 * @param name
 */
    Tag::Tag(std::string _name): name(_name) {
    }

/**
 * @param project_id
 */
    void Tag::GetTagsByProjectId(int project_id) {

    }

    Tag *Tag::getByName(std::string name, int projectId) {
        return this->app->getRepository()->getTagsByName(name, projectId);
    }

    void Tag::SetName(std::string name) {
        this->name = name;
    }

    void Tag::update(const std::string& oldName, const std::string& newName, int projectId) {
        this->app->getRepository()->updateTag(oldName, newName, projectId);
    }

    bool Tag::add(Tag *pTag, int projectId) {
        return this->app->getRepository()->insertTag(pTag, projectId);
    }

    void Tag::remove(std::string tagName, int projectId ) {
        this->app->getRepository()->removeTag(tagName, projectId );
    }

    void Tag::remove(Tag *pTag, int projectId ){
        this->app->getRepository()->removeTag(pTag, projectId );
    }


    void Tag::attachApp(CoreApp* _app){
        this->app = _app;
    }

    std::vector<Tag *> Tag::getByProjectId(int i) {
        return std::vector<Tag *>();
    }
}