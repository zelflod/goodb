#include "Server.h"
#include <string>

int main(){
    char host[] = { '1', '2', '7', '.', '0', '.', '0', '.', '1', '\0'};
    char port[] = { '9', '0', '9', '0', '\0'};
    char rootDir[] = { '.', '\0'};
    char threads[] = { '1', '\0'};

    char * params[5] {nullptr, host, port, rootDir, threads};
    ServerListenAndServe(5, params);

    return 0;
}