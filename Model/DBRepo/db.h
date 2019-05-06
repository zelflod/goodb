
#ifndef GOODB_DB_H
#define GOODB_DB_H

#include <string>

namespace db {
    static const std::string usersTableName = "users";

    class session {
    public:
        bool insert(std::string table_name, std::string value_name, std::string value);

        bool update(std::string table_name, std::string value_name, std::string value, std::string where_name,
                    std::string where_val);

        std::string select_one(std::string table_name, std::string select_name, std::string where_name, std::string where_val);
    };

    static db::session session;
}

#endif //GOODB_DB_H
