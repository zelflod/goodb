

#ifndef GOODB_MOCKREPOSITORY_H
#define GOODB_MOCKREPOSITORY_H

#include "Repository.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>
#include <unordered_map>


#include "Task.h"
#include "User.h"
#include "Project.h"
#include "Folder.h"
#include "Tag.h"

class MockRepository : public Repository {
private:
    std::unordered_map<int, TMApp::Task> tasks;
    std::unordered_map<std::string, TMApp::User> users;
    std::unordered_map<int, TMApp::Project> projects;
    std::unordered_map<std::string, TMApp::Tag> tags;
    std::unordered_map<int, TMApp::Folder> folders;

    int tasksCount = 0;
    int projectsCount = 0;
    int foldersCount = 0;

public:

    std::vector<TMApp::Task *> getTasksByFolderId(int folderId) override;
    
    std::vector<TMApp::Task *> getTasksByDate(std::string date) override;
    
    std::vector<TMApp::Task *> getTasksByDateRange(std::string dateFrom, std::string dateTo) override;
    
    void insertTask(TMApp::Task *pTask, int folderId) override;
    
    TMApp::Task *getTaskById(int id) override;
    
    void updateTask(TMApp::Task *pTask) override;
    
    void removeTask(TMApp::Task *pTask) override;
    
    void removeTask(int taskId) override;
    
    TMApp::Tag *getTagsByName(std::string name, int projectId) override;
    
    void updateTag(const std::string& oldName, const std::string& newName, int projectId) override;
    
    bool insertTag(TMApp::Tag *pTag, int projectId) override;
    
    void removeTag(std::string tagName, int projectId) override;
    
    void removeTag(TMApp::Tag *pTag, int projectId) override;
    
    std::vector<TMApp::Project *> getProjectsByUserId(std::string& userId, bool isDefault) override;
    
    void insertProject(TMApp::Project *pProject) override;
    
    void updateProject(TMApp::Project *&pProject) override;

    TMApp::Folder*  getFolderById(int folderId) override;
    
    void updateFolder(TMApp::Folder *pFolder) override;
    
    void insertFolder(TMApp::Folder *pFolder, int projectId) override;
    
    void removeFolder(TMApp::Folder *pFolder, int projectId) override;
    
    std::vector<TMApp::Folder *> getFoldersByProjectId(int projectId) override;


    void insertUser(TMApp::User *pUser) override;

    void updateUser(TMApp::User *pUser) override;

    TMApp::User *getUserByUsername(std::string username) override;
};


#endif
