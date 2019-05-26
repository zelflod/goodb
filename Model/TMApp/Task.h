

#ifndef _TASK_H
#define _TASK_H

#include <string>
#include <vector>
#include "CoreApp.h"
#include <memory>

namespace TMApp {

    class Task {
    public:
        std::string title;
        std::string description;
        int priority;
        std::string estimatedTime;
        std::string actualTimeSpent;
        std::string assignee;
        std::string dueDate;
        std::string dueTime;
        bool completed;
        int folderId;
        std::string geoPlace;
        std::string plannedCompleteDate;
        std::vector<std::shared_ptr<TMApp::Tag>> tags;

        /**
         * @param title
         */
        Task(std::string title);

        Task(CoreApp * _app);

        Task();

        /**
         * @param name
         * @param folder_id
         */
        Task(std::string name, int folder_id);

        void attachApp(CoreApp* app);

        void Create();

        /**
         * @param folder_id
         */
        void MoveToFolder(int folder_id);

        std::vector<Task *> getByFolderId(int folderId);

        std::vector<Task *> getByDate(std::string date);

        std::vector<Task *> getByDateRange(std::string dateFrom, std::string dateTo);

        void add(int folderId, Task *pTask);

        Task *getById(int taskId);

        void SetCompleted();

        void update(Task *pTask);

        void remove(Task *pTask);

        void remove(int taskId);

        int id;

        bool operator < (const Task& str) const
        {
            return (dueDate < str.dueDate);
        }

    private:
        CoreApp* app;
    };
}



#endif