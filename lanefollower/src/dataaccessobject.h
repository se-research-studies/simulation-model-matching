#pragma once

class DataAccessObject {
public:
    DataAccessObject();
    virtual ~DataAccessObject();

public:
    void beginTransaction() const;
    void endTransaction() const;
};

