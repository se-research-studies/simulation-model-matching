#pragma once

#include <string>

struct TableField {
    TableField(const std::string& field, const std::string& value);

    const std::string field;
    const std::string value;
};
