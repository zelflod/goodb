#define CATCH_CONFIG_MAIN

#include "libs/catch.hpp"
#include "Model/TMApp/TMApp.h"
#include "Model/MockRepository.h"


TEST_CASE("Tag"){
    TMApp::TMApp app;
    app.attachRepository(new MockRepository());
    app.init();

    if (!app.login("username", "psw")) {
        app.signup("username", "psw");
        app.login("username", "psw");
    }

    SECTION("tag adding") {
        bool isAdded = app.tags.add(new TMApp::Tag("new_tag"), 0);
        REQUIRE( isAdded == true);
    }

    SECTION("get existing tag") {
        bool isAdded = app.tags.add(new TMApp::Tag("new_tag"), 0);

        TMApp::Tag * tag = app.tags.getByName("new_tag", 0);
        REQUIRE( tag != nullptr);
    }

    SECTION("try to get nonexisting tag") {
        bool isAdded = app.tags.add(new TMApp::Tag("new_tag"), 0);

        TMApp::Tag * tag = app.tags.getByName("new_tag", 1);
        REQUIRE(tag == nullptr);
    }

    SECTION("update tag") {
        bool isAdded = app.tags.add(new TMApp::Tag("new_tag"), 0);

        TMApp::Tag * tag = app.tags.getByName("new_tag", 0);
        app.tags.update(tag->name, "new_name", 0);

        tag = app.tags.getByName("new_tag", 0);
        TMApp::Tag * tagUpdated = app.tags.getByName("new_name", 0);
        REQUIRE(tag == nullptr);
        REQUIRE(tagUpdated != nullptr);
    }

    SECTION("remove tag") {
        bool isAdded = app.tags.add(new TMApp::Tag("new_tag"), 0);
        TMApp::Tag * tag = app.tags.getByName("new_tag", 0);
        app.tags.remove(tag, 0);

        tag = app.tags.getByName("new_tag", 0);
        REQUIRE(tag == nullptr);

        app.tags.add(new TMApp::Tag("new_tag"), 0);
        app.tags.remove("new_tag", 0);

        tag = app.tags.getByName("new_tag", 0);
        REQUIRE(tag == nullptr);
    }
}

TEST_CASE("Task class"){
    TMApp::TMApp app;
    app.attachRepository(new MockRepository());
    app.init();

    if (!app.login("username", "psw")) {
        app.signup("username", "psw");
        app.login("username", "psw");
    }

    SECTION("add task") {
        app.tasks.add(10, new TMApp::Task("new task"));
    }

    SECTION("get existing task") {
        app.tasks.add(10, new TMApp::Task("new task"));
        TMApp::Task * task = app.tasks.getById(0);
        REQUIRE(task != nullptr);
    }

    SECTION("get nonexistent task") {
        TMApp::Task * task = app.tasks.getById(0);
        REQUIRE(task == nullptr);
    }

    SECTION("get tasks by folder") {
        app.tasks.add(10, new TMApp::Task("new task"));

        std::vector<TMApp::Task *> tasks = app.tasks.getByFolderId(10);

        REQUIRE(tasks.size() == 1);
    }

    SECTION("get tasks by due-date") {
        TMApp::Task * task = new TMApp::Task("new task");
        std::string dueDate = "10/10/2020";
        task->dueDate = dueDate;
        app.tasks.add(10, task);
        std::vector<TMApp::Task *> tasks = app.tasks.getByDate(dueDate);

        REQUIRE(tasks.size() == 1);
    }

    SECTION("update task") {
        TMApp::Task * task = new TMApp::Task("new task");
        std::string dueDate = "10/10/2020";
        task->dueDate = dueDate;
        app.tasks.add(10, task);

        task = app.tasks.getById(0);

        dueDate = "20/12/2030";
        task->completed = true;
        task->dueDate = dueDate;
        task->priority = 1;

        app.tasks.update(task);

        task = app.tasks.getById(0);

        REQUIRE(task->priority == 1);
        REQUIRE(task->dueDate == dueDate);
        REQUIRE(task->completed == true);
    }

    SECTION("remove task") {
        app.tasks.add(10, new TMApp::Task("new task"));

        TMApp::Task * task = app.tasks.getById(0);

        app.tasks.remove(task);

        task = app.tasks.getById(0);

        REQUIRE(task == nullptr);
    }

    SECTION("remove task by id") {
        app.tasks.add(10, new TMApp::Task("new task"));

        app.tasks.remove(0);

        TMApp::Task * task = app.tasks.getById(0);

        REQUIRE(task == nullptr);
    }

}


TEST_CASE("TMApp"){
    TMApp::TMApp app;
    app.attachRepository(new MockRepository());
    app.init();

    SECTION("check actions with user") {
        if (!app.login("username", "psw")) {
            app.signup("username", "psw");
            app.login("username", "psw");
        }
        TMApp::User* u = app.getUser();
        std::cout << app.getUsername() << std::endl;
        std::cout << u->getUsername() << std::endl;

        if (u->VerifyPassword("psw")) {
            std::cout << "password is correct" << std::endl;
        }
        u->SetUsername("new_name");
        u->SetPassword("new password");

        if (!u->VerifyPassword("psw")) {
            std::cout << "password is NOT correct" << std::endl;
        }
    }

    SECTION("check actions with project") {
        if (!app.login("username", "psw")) {
            app.signup("username", "psw");
            app.login("username", "psw");
        }

        TMApp::Project* project = app.projects.getDefault();
        if (project == nullptr) {
            app.projects.setDefault(new TMApp::Project());
        }
        project = app.projects.getDefault();
        if (project->is_default) {
            std::cout << "is default"  << std::endl;
        }
        std::vector<TMApp::Project *> projects = app.projects.getAll();
        std::cout << projects.size();
        if (!projects.empty()){
            projects[0]->SetName("new name");
            app.projects.update(projects[0]);
            projects = app.projects.getAll();
            std::cout << projects[0]->name  << std::endl;
        }
    }


    SECTION("check actions with folder") {
        app.folders.add(new TMApp::Folder("folder name"), 1);
        std::vector<TMApp::Folder *> folders = app.folders.getByProjectId(1);
        TMApp::Folder* folder = app.folders.getById(0);
        app.folders.update(folder);
        app.folders.remove(folder, 1);
    }

    SECTION("check actions with task") {
        int folderId = 10;
        app.tasks.add(folderId, new TMApp::Task(""));
        std::vector<TMApp::Task *> tasks = app.tasks.getByFolderId(folderId);
        tasks = app.tasks.getByDate("10/11/2019");
        tasks = app.tasks.getByDateRange("10/11/2019", "10/11/2019");
        TMApp::Task * task = app.tasks.getById(0);
        app.tasks.update(task);
        app.tasks.remove(task);
        app.tasks.remove(0);
    }


}


TEST_CASE("User class"){

    TMApp::TMApp app;
    app.attachRepository(new MockRepository());
    app.init();

    std::string psw = "psw";
    if (!app.login("username", psw)) {
        app.signup("username", psw);
        app.login("username", psw);
    }

    SECTION("check existence of public methods") {
        TMApp::User user("username");
        if (user.hasDataAccess()) {
            user.Create();
            user.SetPassword(std::string("password"));
            user.VerifyPassword(std::string("password"));
        }
        user.~User();
    }

    SECTION("if correct password is provided then password is successfully verified"){
        REQUIRE(app.getUser()->VerifyPassword(psw) == true);

    }

    SECTION("if wrong password is provided then password verification is failed"){
        REQUIRE(app.getUser()->VerifyPassword("wrong password") == false);
    }

    SECTION("set password"){
        std::string newPassword = "new password";
        app.getUser()->SetPassword(newPassword);
        REQUIRE(app.getUser()->VerifyPassword(newPassword) == true);
    }
}

TEST_CASE("Project"){
    TMApp::TMApp app;
    app.attachRepository(new MockRepository());
    app.init();

    if (!app.login("username", "psw")) {
        app.signup("username", "psw");
        app.login("username", "psw");
    }

    SECTION("check actions with project") {
        TMApp::Project* project = app.projects.getDefault();
        if (project == nullptr) {
            app.projects.setDefault(new TMApp::Project());
        }
        project = app.projects.getDefault();
        if (project->is_default) {
            std::cout << "is default"  << std::endl;
        }
        std::vector<TMApp::Project *> projects = app.projects.getAll();
        std::cout << projects.size();
        if (!projects.empty()){
            projects[0]->SetName("new name");
            app.projects.update(projects[0]);
            projects = app.projects.getAll();
            std::cout << projects[0]->name  << std::endl;
        }
    }
}


TEST_CASE("Folder class"){
    TMApp::TMApp app;
    app.attachRepository(new MockRepository());
    app.init();

    if (!app.login("username", "psw")) {
        app.signup("username", "psw");
        app.login("username", "psw");
    }

    SECTION("add folder") {
        app.folders.add(new TMApp::Folder("folder name"), 1);
    }

    SECTION("get existing folder") {
        app.folders.add(new TMApp::Folder("folder name"), 1);

        TMApp::Folder* folder = app.folders.getById(0);
        REQUIRE(folder != nullptr);

    }

    SECTION("get nonexistent folder") {
        TMApp::Folder* folder = app.folders.getById(0);
        REQUIRE(folder == nullptr);
    }

    SECTION("get folder by project") {
        app.folders.add(new TMApp::Folder("folder name"), 1);

        std::vector<TMApp::Folder *> folders = app.folders.getByProjectId(1);

        REQUIRE(folders.size() == 1);
    }

    SECTION("update folder") {
        app.folders.add(new TMApp::Folder("folder name"), 1);

        TMApp::Folder* folder = app.folders.getById(0);
        folder->SetName("new folder name");
        app.folders.update(folder);
        folder = app.folders.getById(0);

        REQUIRE(folder->name == "new folder name");
    }

    SECTION("remove folder") {
        app.folders.add(new TMApp::Folder("folder name"), 1);

        TMApp::Folder* folder = app.folders.getById(0);

        REQUIRE(folder != nullptr);

        app.folders.remove(folder, 1);

        folder = app.folders.getById(0);

        REQUIRE(folder == nullptr);
    }
}

//SCENARIO( "History is created after Task creation", "[task]" ) {
//    WHEN( "a task is created" ) {
//        TMApp::Task *task = new TMApp::Task("");
//
//        THEN( "the first task's history item is 'Task created'" ) {
////            TMApp::History *history = task.getHistory();
////            REQUIRE( history->executions[0]->title == TASK_CREATED_TITLE);
//        }
//    }
//}