#include "tablecolumn.h"

namespace Common {
  TableColumn::TableColumn(const std::string& name, const std::string& type)
    : name(name), type(type) {
  }
}
