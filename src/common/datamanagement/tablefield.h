#pragma once

#include <string>

namespace Common {
struct TableField {
    TableField(const std::string& _field, const std::string& _value);

    const std::string field;
    const std::string value;
};
}
