#pragma once

#include <string>

namespace Common {
struct TableColumn {
    TableColumn(const std::string& _name, const std::string& _type);

    const std::string name;
    const std::string type;
};
}

