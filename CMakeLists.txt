cmake_minimum_required(VERSION 3.10)
project(goodb)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Model)
include_directories(Model/TMApp)
include_directories(Model/DBRepo)
include_directories(Model/NetRepo)

add_executable(unit-test
        Model/Test/test.cpp
        Model/MockRepository.cpp
        Model/DBRepo/db.cpp
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

#add_subdirectory (Server)




set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lboost_system ") #-lssl -lcrypto -ldl -lz
# -lboost_system-m

SET (BOOST_ROOT "/usr/local/boost_1_70_0")
set(Boost_USE_STATIC_LIBS OFF)

find_package(Boost REQUIRED COMPONENTS log)
find_package(Threads REQUIRED)

find_package(OpenSSL 1.0.1 REQUIRED)
set(OPENSSL_VERSION "1.0.1")

# Configure compiler options ...
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message("-- configuring clang options")
    set(CMAKE_CXX_FLAGS "-arch x86_64 -std=c++11 -stdlib=libc++ -DBOOST_LOG_DYN_LINK -Wno-deprecated-declarations")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message("-- configuring gcc options")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -DBOOST_LOG_DYN_LINK")
endif()

add_executable(server_service server_service/main.cpp
        server_service/app_server.cpp
        server_service/core/network_utils.cpp
        server_service/core/basic_server.cpp
        Model/MockRepository.cpp
        Model/DBRepo/db.cpp
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

set(CPPRESTSDK_INCLUDE_DIR "./libs/cpprestsdk/Release/include")
set(MICROSERVICE_INCLUDE_DIR "server_service/core/include")
set(HEADER_SEARCH_PATHS ${MICROSERVICE_INCLUDE_DIR} ${CPPRESTSDK_INCLUDE_DIR}  ${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR} )
include_directories(${HEADER_SEARCH_PATHS})

set(CPPRESTSDK_LIBRARY "${PROJECT_SOURCE_DIR}/libs/cpprestsdk/build.release/Binaries/libcpprest.a")
set(OPENSSL_LIBS  "${OPENSSL_LIBRARIES}")



set(LIBRARIES_SEARCH_PATHS ${CPPRESTSDK_LIBRARY} ${Boost_LIBRARIES} ${OPENSSL_LIBS})
target_link_libraries(server_service ${LIBRARIES_SEARCH_PATHS})

#find_library(CPPREST_LIB cpprest)
#target_link_libraries(server_service ${CPPRESTSDK_LIBRARY} ${Boost_LIBRARIES} OpenSSL::SSL)
