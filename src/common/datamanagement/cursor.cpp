#include "cursor.h"

namespace Common {

Cursor::Cursor(sqlite3_stmt* _statement)
    : statement(_statement) {
}

Cursor::Cursor(Cursor&& other)
    : statement(std::move(other.statement)) {
}

Cursor::~Cursor() {
    sqlite3_finalize(statement);
}

bool Cursor::moveToNext() {
    return sqlite3_step(statement) == SQLITE_ROW;
}

std::string Cursor::getString(uint8_t column) const {
    const unsigned char* result = sqlite3_column_text(statement, column);
    if (result == nullptr) {
        return "NULL";
    } else {
        return std::string(reinterpret_cast<const char*>(result));
    }
}

uint32_t Cursor::getUInt(uint8_t column) const {
    return sqlite3_column_int(statement, column);
}

uint16_t Cursor::getUShort(uint8_t column) const {
    return sqlite3_column_int(statement, column);
}

} // namespace Common
