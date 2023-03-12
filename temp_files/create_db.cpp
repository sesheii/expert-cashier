#include <iostream>
#include "sqlite/sqlite3.h"

int main()
{
    sqlite3* db;
    int rc = sqlite3_open("database.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    std::string create_table_sql = "CREATE TABLE users ("
                                   "name TEXT,"
                                   "surname TEXT,"
                                   "id TEXT,"
                                   "income TEXT,"
                                   "age TEXT"
                                   ")";
    char* error_msg = nullptr;
    rc = sqlite3_exec(db, create_table_sql.c_str(), nullptr, nullptr, &error_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error creating table: " << error_msg << std::endl;
        sqlite3_free(error_msg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    return 0;
}
