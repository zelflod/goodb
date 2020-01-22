# goodb

Все задачи отслеживаются в [Github Projects](https://github.com/nozimy/goodb/projects/1) и в Trello


###libs:

- boost v1.70
- catch v2.7.2
- cpprestsdk v2.10.6

###build

        mkdir build
        cd build
        cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..

###run server: On ```./build``` directory type

        ./server_service

        or

        ./server_service $IP $PORT

        for example: ./server_service 127.0.1.1 9090

###test: On ```./build``` directory type

        ./unit-test



