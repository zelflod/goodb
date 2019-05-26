# goodb

Client web-app demo available at https://floating-taiga-93491.herokuapp.com

[Api server](https://infinite-mountain-23771.herokuapp.com/api/tasks) is in another heroku dyno. Used this [buildpack](https://elements.heroku.com/buildpacks/starkast/heroku-buildpack-cmake)

Все задачи отслеживаются в [Github Projects](https://github.com/nozimy/goodb/projects/1) и в Trello


### libs:

- boost v1.70
- catch v2.7.2
- cpprestsdk v2.10.6

### build

        mkdir build
        cd build
        cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..

### type the command:
        
        make -j 8
        
### run server: On ```./build``` directory type

        ./server_service

        or

        ./server_service $IP $PORT

        for example: ./server_service 127.0.1.1 9090

### test: On ```./build``` directory type

        ./unit-test



