// user_database.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<sqlite3.h>
#include<string>


using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}


int createDB() {
    sqlite3* db;
    int database = 0;

    database = sqlite3_open("USER_DATABASE.db", &db);

    if (database) {
        cerr << "Error opening database" << sqlite3_errmsg(db) << endl;
        return -1;
    }
    else {
        cout << "Database opened successfully" << endl;
        sqlite3_close(db);
    }
    return 0;
}

int createTable(){
    sqlite3* db;
    string sql = "CREATE TABLE IF NOT EXISTS CREDENTIALS("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "UID       TEXT NOT NULL, "
        "Password  TEXT NOT NULL );";

    try {
        int exit = 0;
        exit = sqlite3_open("USER_DATABASE.db", &db);
        char* errormessage;
        exit = sqlite3_exec(db, sql.c_str(), NULL, 0, &errormessage);

        if (exit != SQLITE_OK) {
            cerr << "Error creating the table" << endl;
            sqlite3_free(errormessage);

        }
        else {
            cout << "Table created successfully" << endl;
        }
        sqlite3_close(db);

    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return -1;
    }
    return 0;
}

void insertToTable() {
    sqlite3* db;
    char* errorMessage;
    int exit = sqlite3_open("USER_DATABASE.db", &db);

    string insertSql = "INSERT INTO CREDENTIALS VALUES(2, 'user2', 'user234');";
    string querySql = "SELECT * FROM CREDENTIALS;";
    exit = sqlite3_exec(db, insertSql.c_str(), NULL, 0, &errorMessage);

    if (exit != SQLITE_OK) {
        cerr << "Error inserting values to the table" << endl;
        sqlite3_free(errorMessage);
    }
    else {
        cout << "Value added to the table" << endl;
        sqlite3_exec(db, querySql.c_str(), callback, NULL, NULL);
    }
    sqlite3_close(db);
}


int main()
{   
    int i = createDB();
    int j = createTable();
    insertToTable();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

