#pragma once

#include <string>
#include <vector>

#include <sqlite3.h>

#include <FeatureSimulationCommon/DataManagement/Cursor>
#include <FeatureSimulationCommon/DataManagement/TableField>

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
    void beginTransaction();
    void endTransaction();
    Cursor query(const std::string& table, const std::vector<std::string>& columns, const std::string& selection);
    void insert(const std::string& table, const std::vector<TableField>& content);
    void deleteRows(const std::string& table, const std::string& selection);

  private:
    void open();
    void execSql(const std::string& sql);
    std::string buildColumnsString(const std::vector<std::string>& columns) const;
    std::pair<std::string, std::string> buildContentStrings(const std::vector<TableField>& content) const;

  private:
    std::string DB_FILENAME = "data.sqlite";

  private:
    sqlite3* db;
    bool isOpen = false;
  };

} // namespace Common
