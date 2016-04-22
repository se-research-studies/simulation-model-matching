#pragma once

#include <string>

#include <sqlite3.h>

namespace Common {

  class Cursor
  {
  public:
    Cursor(sqlite3_stmt* statement);
    virtual ~Cursor();

  public:
    bool moveToNext();
    std::string getString(uint8_t column);
    uint32_t getUInt(uint8_t column);
    uint16_t getUShort(uint8_t column);

  private:
    sqlite3_stmt* statement;
  };

} // namespace Common

