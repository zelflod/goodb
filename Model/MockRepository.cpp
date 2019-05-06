

#include "MockRepository.h"


std::vector<TMApp::Task *>MockRepository::getTasksByFolderId(int folderId) {
    std::vector<TMApp::Task *> list;
    for (auto& item : tasks) {
        if (item.second.folderId == folderId) {
            list.push_back(&item.second);
        }
    }
    return list;
}

std::vector<TMApp::Task *>MockRepository::getTasksByDate(std::string date) {
    std::vector<TMApp::Task *> list;
    for (auto& item : tasks) {
        if (item.second.dueDate == date) {
            list.push_back(&item.second);
        }
    }
    return list;
}

std::vector<TMApp::Task *>MockRepository::getTasksByDateRange(std::string dateFrom, std::string dateTo) {

    return std::vector<TMApp::Task *>();
}

TMApp::Task* MockRepository::getTaskById(int id) {
    if (tasks.find(id) != tasks.end()) {
        return &tasks[id];
    }
    return nullptr;
}

void MockRepository::updateTask(TMApp::Task *pTask) {
    if (tasks.find(pTask->id) != tasks.end()) {
        tasks[pTask->id] = *pTask;
    }
}

void MockRepository::removeTask(TMApp::Task *pTask) {
    tasks.erase(pTask->id);
}

void MockRepository::insertTask(TMApp::Task *pTask, int folderId){
    if (!tasks.empty() || tasks.find(tasksCount) != tasks.end()) {
        ++tasksCount;
    }
    pTask->id = tasksCount;
    pTask->folderId = folderId;
    tasks[tasksCount] = *pTask;
    ++tasksCount;
}

void MockRepository::removeTask(int taskId) {
    tasks.erase(taskId);
}




TMApp::Tag* MockRepository::getTagsByName(std::string name, int projectId) {
    std::string key = name + std::to_string(projectId);
    if (tags.find(key) != tags.end()) {
        return &tags[key];
    }
    return nullptr;
}

bool MockRepository::insertTag(TMApp::Tag *pTag, int projectId) {
    std::string key = pTag->name + std::to_string(projectId);
    if (tags.empty() || tags.find(key) == tags.end()) {
        pTag->projectId = projectId;
        tags[key] = *pTag;
        return true;
    }
    return false;
}

void MockRepository::removeTag(std::string tagName, int projectId) {
    std::string key = tagName + std::to_string(projectId);
    tags.erase(key);
}

void MockRepository::updateTag(const std::string& oldName, const std::string& newName, int projectId) {
    std::string key = oldName + std::to_string(projectId);
    if (tags.find(key) != tags.end()) {
        TMApp::Tag  tag = tags[key];
        tag.name = newName;
        tags.erase(key);
        key = newName + std::to_string(projectId);
        tags[key] = tag;
    }
}

void MockRepository::removeTag(TMApp::Tag *pTag, int projectId){
    std::string key = pTag->name + std::to_string(projectId);
    tags.erase(key);
}



void MockRepository::insertProject(TMApp::Project *pProject){
    if (!projects.empty() || projects.find(projectsCount) != projects.end()) {
        ++projectsCount;
    }
    pProject->setId(projectsCount);
    projects[projectsCount] = *pProject;
    ++projectsCount;
}

std::vector<TMApp::Project *>MockRepository::getProjectsByUserId(std::string& userId, bool isDefault) {
    std::vector<TMApp::Project *> list;
    for (auto& item : projects) {
//        if (item.second.getUserId() == userId && item.second.is_default == isDefault) {
        if (item.second.getUserId() == userId) {
            list.push_back(&item.second);
        }
    }
    return list;
}

void MockRepository::updateProject(TMApp::Project *&pProject) {
    if (projects.find(pProject->getId()) != projects.end()) {
        projects[pProject->getId()] = *pProject;
    }
}


void MockRepository::insertFolder(TMApp::Folder *pFolder, int projectId) {
    if (!folders.empty() || folders.find(foldersCount) != folders.end()) {
        ++foldersCount;
    }
    pFolder->id = foldersCount;
    pFolder->projectId = projectId;
    folders[foldersCount] = *pFolder;
    ++foldersCount;
}

TMApp::Folder* MockRepository::getFolderById(int folderId) {
    if (folders.find(folderId) != folders.end()) {
        return &folders[folderId];
    }
    return nullptr;
}

void MockRepository::removeFolder(TMApp::Folder *pFolder, int projectId) {
    folders.erase(pFolder->id);
}

std::vector<TMApp::Folder *> MockRepository::getFoldersByProjectId(int projectId) {
    std::vector<TMApp::Folder *> list;
    for (auto& item : folders) {
        if (item.second.projectId == projectId) {
            list.push_back(&item.second);
        }
    }
    return list;
}

void MockRepository::updateFolder(TMApp::Folder *pFolder){
    if (folders.find(pFolder->id) != folders.end()) {
        folders[pFolder->id] = *pFolder;
    }
}



void MockRepository::insertUser(TMApp::User *pUser){
    if (users.empty() || users.find(pUser->getUsername()) == users.end()) {
        users[pUser->getUsername()] = *pUser;
    }
}

void MockRepository::updateUser(TMApp::User *pUser) {
    if (users.find(pUser->getUsername()) != users.end()) {
        users[pUser->getUsername()] = *pUser;
    }
}

TMApp::User* MockRepository::getUserByUsername(std::string username) {
    if (users.find(username) != users.end()) {
        return &users[username];
    }
    return nullptr;
}