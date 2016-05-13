#include "tablefield.h"

namespace Common {
  TableField::TableField(const std::string& field, const std::string& value)
    : field(field), value(value) {
  }
}
