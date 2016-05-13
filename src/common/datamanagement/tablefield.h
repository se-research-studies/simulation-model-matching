#pragma once

#include <string>

namespace Common {
  struct TableField {
    TableField(const std::string& field, const std::string& value);

    const std::string field;
    const std::string value;
  };
}
