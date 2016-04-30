#pragma once

namespace Common {

  class DataAccessObject {
  public:
    DataAccessObject();
    virtual ~DataAccessObject();

  public:
    void beginTransaction() const;
    void endTransaction() const;
  };

} // namespace Common

