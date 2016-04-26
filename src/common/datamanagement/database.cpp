#include "database.h"

#include <stdexcept>

namespace Common {

  Database::Database() {
  }

  Database::~Database() {
    if (isOpen) {
      sqlite3_close(db);
    }
  }

  Database& Database::getInstance() {
    static Database instance;
    instance.open();
    return instance;
  }

  void Database::open() {
    if (!isOpen) {
      if (sqlite3_open(DB_FILENAME.c_str(), &db) == SQLITE_OK) {
        isOpen = true;
      } else {
        throw std::runtime_error(sqlite3_errmsg(db));
      }
    }
  }

  void Database::beginTransaction() {
    execSql("BEGIN TRANSACTION;");
  }

  void Database::endTransaction() {
    execSql("END TRANSACTION;");
  }

  Cursor Database::query(const std::string& table, const std::vector<std::string>& columns, const std::string& selection) {
    std::string columnsString = buildColumnsString(columns);
    std::string sql = "SELECT " + columnsString + " FROM " + table + " WHERE " + selection;
    sqlite3_stmt* statement;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
      throw std::runtime_error(sqlite3_errmsg(db));
    }
    return Cursor(statement);
  }

  void Database::insert(const std::string& table, const std::vector<TableField>& content) {
    std::pair<std::string, std::string> contentStrings = buildContentStrings(content);
    std::string sql = "INSERT INTO " + table + " (" + contentStrings.first + ") VALUES (" + contentStrings.second + ");";
    execSql(sql);
  }

  void Database::deleteRows(const std::string& table, const std::string& selection)
  {
    std::string sql = "DELETE FROM " + table;
    if (selection.size() > 0) {
      sql += " WHERE " + selection;
    }
    execSql(sql);
  }

  void Database::execSql(const std::string& sql) {
    char* errorMessage;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
      throw std::runtime_error(errorMessage);
    }
  }

  std::string Database::buildColumnsString(const std::vector<std::string>& columns) const {
    std::string result;
    for (const std::string& column : columns) {
      result += column + ",";
    }
    result.pop_back();
    return result;
  }

  std::pair<std::string, std::string> Database::buildContentStrings(const std::vector<TableField>& content) const {
    std::string columns;
    std::string values;
    for (const TableField& tableField : content) {
      columns += tableField.field + ",";
      values += "'" + tableField.value + "',";
    }
    columns.pop_back();
    values.pop_back();
    return std::make_pair(columns, values);
  }

} // namespace Common
