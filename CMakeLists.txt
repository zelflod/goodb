cmake_minimum_required(VERSION 3.13)
project(goodb)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Model)
include_directories(Model/TMApp)
include_directories(Model/DBRepo)
include_directories(Model/NetRepo)

add_executable(test
        Model/MockRepository.cpp
        Model/DBRepo/db.cpp
        Model/Test/test.cpp
        Model/TMApp/TMApp.cpp
        Model/TMApp/Tag.cpp
        Model/TMApp/Task.cpp
        Model/TMApp/Execution.cpp
        Model/TMApp/Folder.cpp
        Model/TMApp/History.cpp
        Model/TMApp/Project.cpp
        Model/TMApp/sha256.cpp
        Model/TMApp/User.cpp
        Model/TMApp/utils.cpp
        Model/TMApp/MutuallyAttachable.cpp

        )

add_subdirectory (Server)
