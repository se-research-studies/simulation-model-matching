#include "database.h"

#include <stdexcept>

#include <FeatureSimulation/Common/utils.h>

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
    return instance;
}

void Database::setDbFilename(const std::string& argv0, const std::string& value)
{
    if (value.compare(0, 3, "../") == 0) {
        std::string executableFolder = Utils::fileFolderPath(argv0);
        dbFilename = "file:" + executableFolder + "/" + value;
    } else {
        dbFilename = value;
    }
    getInstance().open();
}

void Database::open() {
    if (!isOpen) {
        if (sqlite3_open_v2(dbFilename.c_str(), &db, SQLITE_OPEN_URI | SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL) == SQLITE_OK) {
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

void Database::createTable(const std::string& table, const std::vector<TableColumn>& columns) {
    std::string columnsString = buildCreateTableColumnsString(columns);
    std::string sql = "CREATE TABLE IF NOT EXISTS " + table + " " + columnsString + ";";
    execSql(sql);
}

Cursor Database::query(const std::string& table, const std::vector<std::string>& columns, const std::string& selection) {
    std::string columnsString = buildSelectColumnsString(columns);
    std::string sql = "SELECT " + columnsString + " FROM " + table + " WHERE " + selection + ";";
    sqlite3_stmt* statement;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &statement, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db));
    }
    return Cursor(statement);
}

void Database::insert(const std::string& table, const std::vector<TableField>& content) {
    std::pair<std::string, std::string> contentStrings = buildInsertContentStrings(content);
    std::string sql = "INSERT INTO " + table + " (" + contentStrings.first + ") VALUES (" + contentStrings.second + ");";
    execSql(sql);
}

void Database::deleteRows(const std::string& table, const std::string& selection) {
    std::string sql = "DELETE FROM " + table;
    if (selection.size() > 0) {
        sql += " WHERE " + selection;
    }
    sql += ";";
    execSql(sql);
}

void Database::execSql(const std::string& sql) {
    char* errorMessage;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        throw std::runtime_error(errorMessage);
    }
}

std::string Database::buildCreateTableColumnsString(const std::vector<TableColumn>& columns) const {
    if (columns.size() > 0) {
        std::string result = "(";
        for (const TableColumn& tableColumn : columns) {
            result += tableColumn.name + " " + tableColumn.type + ",";
        }
        result.pop_back();
        result += ")";
        return result;
    } else {
        throw std::runtime_error("Common::Database: CREATE TABLE without columns");
    }
}

std::string Database::buildSelectColumnsString(const std::vector<std::string>& columns) const {
    if (columns.size() > 0) {
        std::string result;
        for (const std::string& column : columns) {
            result += column + ",";
        }
        result.pop_back();
        return result;
    } else {
        throw std::runtime_error("Common::Database: SELECT clause without columns");
    }
}

std::pair<std::string, std::string> Database::buildInsertContentStrings(const std::vector<TableField>& content) const {
    if (content.size() > 0) {
        std::string columns;
        std::string values;
        for (const TableField& tableField : content) {
            columns += tableField.field + ",";
            values += "'" + tableField.value + "',";
        }
        columns.pop_back();
        values.pop_back();
        return std::make_pair(columns, values);
    } else {
        throw std::runtime_error("Common::Database: INSERT without content");
    }
}

} // namespace Common
