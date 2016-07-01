#pragma once

#include <string>
#include <vector>

#include <sqlite3.h>

#include <FeatureSimulation/Common/DataManagement/cursor.h>
#include <FeatureSimulation/Common/DataManagement/tablecolumn.h>
#include <FeatureSimulation/Common/DataManagement/tablefield.h>

namespace Common {

class Database {
public:
    virtual ~Database();

public:
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

private:
    Database();

public:
    static Database& getInstance();

public:
    void setDbFilename(const std::string& argv0, const std::string& value);
    void beginTransaction();
    void endTransaction();
    void createTable(const std::string& table, const std::vector<TableColumn>& columns);
    Cursor query(const std::string& table, const std::vector<std::string>& columns, const std::string& selection);
    void insert(const std::string& table, const std::vector<TableField>& content);
    void deleteRows(const std::string& table, const std::string& selection);

private:
    void open();
    void execSql(const std::string& sql);
    std::string buildCreateTableColumnsString(const std::vector<TableColumn>& columns) const;
    std::string buildSelectColumnsString(const std::vector<std::string>& columns) const;
    std::pair<std::string, std::string> buildInsertContentStrings(const std::vector<TableField>& content) const;

private:
    std::string dbFilename = "data.sqlite";

private:
    sqlite3* db = nullptr;
    bool isOpen = false;
};

} // namespace Common

