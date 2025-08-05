#pragma once

#include <memory>

#include "utils.hpp"

namespace Plutus {

class AbstractController {
public:
  explicit AbstractController(std::shared_ptr<Table> _table, std::shared_ptr<sql::Database> _db)
      : table(_table), db(_db) {}

  virtual Result Insert() { return {true, ""}; }
  virtual Result Remove() { return {true, ""}; }
  virtual Result Update() { return {true, ""}; }

  virtual void UpdateTable() {}

protected:
  std::shared_ptr<Table> table = nullptr;
  std::shared_ptr<sql::Database> db = nullptr;
};

} // namespace Plutus
