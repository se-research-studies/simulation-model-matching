#pragma once

#include <string>

struct TableColumn {
    TableColumn(const std::string& name, const std::string& type);

    const std::string name;
    const std::string type;
};

