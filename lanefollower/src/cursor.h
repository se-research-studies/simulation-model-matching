#pragma once

#include <string>

#include <sqlite3.h>

class Cursor {
public:
    Cursor(sqlite3_stmt* statement);
    Cursor(Cursor&& other);
    virtual ~Cursor();

public:
    Cursor(const Cursor&) = delete;
    Cursor& operator=(const Cursor&) = delete;

public:
    bool moveToNext();
    std::string getString(uint8_t column) const;
    uint32_t getUInt(uint8_t column) const;
    uint16_t getUShort(uint8_t column) const;

private:
    sqlite3_stmt* statement;
};


