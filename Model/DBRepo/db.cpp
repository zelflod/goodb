
#include "db.h"
#include <cppdb/frontend.h>

//static cppdb::session sql;

namespace db {

//    session::operator<<(std::string const &q)
//    {
//
//    }
//
//    session::operator<<(char const *s)
//    {
//
//    }

    bool session::insert(std::string table_name, std::string value_name, std::string value){
//        sql
//            << "INSERT OR IGNORE INTO " << table_name << " (" << value_name << ") VALUES (?)"
//            << value
//            << cppdb::exec;
        return true;
    }

    std::string session::select_one(std::string table_name, std::string select_name, std::string where_name, std::string where_val){
//        cppdb::result r = sql
//                << "SELECT " << select_name <<" FROM " << table_name <<" WHERE " << where_name <<" = ?"
//                << where_val
//                << cppdb::row;
//        if (r.empty()) {
            return std::string("");
//        }
//        return r.get<std::string>(select_name);;
    }

    bool session::update(std::string table_name, std::string value_name, std::string value, std::string where_name, std::string where_val){
//        sql
//            << "UPDATE " << table_name <<" SET " << value_name << " = ? WHERE " << where_name << " = ?"
//            << value
//            << where_val
//            << cppdb::exec;
        return true;
    }


}