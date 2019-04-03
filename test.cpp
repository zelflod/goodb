#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "./Classes/Task.h"
#include "./Classes/History.h"

const std::string TASK_CREATED_TITLE = "Task created";

SCENARIO( "History is created after Task creation", "[task]" ) {
    WHEN( "a task is created" ) {
        Task *task = new Task();

        THEN( "the first task's history item is 'Task created'" ) {
            History *history = task.getHistory();
            REQUIRE( history->executions[0]->title == TASK_CREATED_TITLE);
        }
    }
}
