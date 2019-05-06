# https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html

SET (BOOST_ROOT "/usr/local/boost_1_70_0")

find_package(Boost 1.70.0 REQUIRED COMPONENTS regex)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(.)
link_directories(.)

#add_executable(Server.cpp Server.cpp)

add_executable (ServerMain
        ${BOOST_BEAST_FILES}
        main.cpp
        Server.cpp
        )

target_link_libraries(ServerMain ${Boost_LIBRARIES}) #you need to link an executable to the located library

set_property(TARGET ServerMain PROPERTY FOLDER "example-http-server")