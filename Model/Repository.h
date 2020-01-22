
#ifndef GOODB_REPOSITORY_H
#define GOODB_REPOSITORY_H

#include <string>
#include <vector>

namespace TMApp {
    class Task;
    class Tag;
    class Project;
    class Folder;
    class User;
}

class Repository {
public:

    virtual std::vector<TMApp::Task *> getTasksByFolderId(int folderId) = 0;

    virtual std::vector<TMApp::Task *> getTasksByDate(std::string date) = 0;

    virtual std::vector<TMApp::Task *> getTasksByDateRange(std::string dateFrom, std::string dateTo) = 0;

    virtual void insertTask(TMApp::Task *pTask, int folderId) = 0;

    virtual TMApp::Task *getTaskById(int id) = 0;

    virtual void updateTask(TMApp::Task *pTask) = 0;

    virtual void removeTask(TMApp::Task *pTask) = 0;

    virtual void removeTask(int taskId) = 0;

    virtual TMApp::Tag *getTagsByName(std::string name, int projectId) = 0;

    virtual void updateTag(const std::string& oldName, const std::string& newName, int projectId) = 0;

    virtual bool insertTag(TMApp::Tag *pTag, int projectId) = 0;

    virtual void removeTag(std::string tagName, int projectId) = 0;

    virtual void removeTag(TMApp::Tag *pTag, int projectId) = 0;

    virtual std::vector<TMApp::Project *> getProjectsByUserId(std::string& userId, bool isDefault) = 0;

    virtual void insertProject(TMApp::Project *pProject) = 0;

    virtual void updateProject(TMApp::Project *&pProject) = 0;

    virtual TMApp::Folder*  getFolderById(int folderId) = 0;

    virtual void updateFolder(TMApp::Folder *pFolder) = 0;

    virtual void insertFolder(TMApp::Folder *pFolder, int projectId) = 0;

    virtual void removeFolder(TMApp::Folder *pFolder, int projectId) = 0;

    virtual std::vector<TMApp::Folder *> getFoldersByProjectId(int projectId) = 0;

    virtual void insertUser(TMApp::User *pUser) = 0;

    virtual void updateUser(TMApp::User *pUser) = 0;

    virtual TMApp::User *getUserByUsername(std::string username) = 0;
};


#endif
