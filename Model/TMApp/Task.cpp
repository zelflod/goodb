/**
 * Project OrganizeMe
 */


#include "Task.h"

/**
 * Task implementation
 */

namespace TMApp {

    Task::Task() {}

    Task::Task(CoreApp* _app): app(_app) {}

    /**
     * @param title
     */
    Task::Task(std::string _title): title(_title), priority(0), completed(false) {
    }

    /**
     * @param title
     * @param folderId
     */
    Task::Task(std::string _title, int _folderId):  title(_title), priority(0), completed(false), folderId(_folderId){
    }

    void Task::Create() {

    }

    /**
     * @param folderId
     */
    void Task::MoveToFolder(int folderId) {
    }

    std::vector<Task *> Task::getByFolderId(int _folderId) {
        return this->app->getRepository()->getTasksByFolderId(_folderId);
    }

    std::vector<Task *> Task::getByDate(std::string date) {
        return this->app->getRepository()->getTasksByDate(date);
    }

    std::vector<Task *> Task::getByDateRange(std::string dateFrom, std::string dateTo) {
        return this->app->getRepository()->getTasksByDateRange(dateFrom, dateTo);
    }

    void Task::add(int _folderId, Task *pTask) {
        return this->app->getRepository()->insertTask(pTask, _folderId);
    }

    Task *Task::getById(int taskId) {
        return this->app->getRepository()->getTaskById(taskId);
    }

    void Task::SetCompleted() {
        this->completed = true;
    }

    void Task::update(Task *pTask) {
        return this->app->getRepository()->updateTask(pTask);
    }

    void Task::remove(Task *pTask) {
        return this->app->getRepository()->removeTask(pTask);
    }

    void Task::remove(int taskId) {
        return this->app->getRepository()->removeTask(taskId);
    }

    void Task::attachApp(CoreApp* _app){
        this->app = _app;
    }
}