#include "controllers/category.hpp"

#include "models/category.hpp"
#include "sql.hpp"
#include "utils.hpp"
#include <memory>

namespace Plutus {

CategoryController::CategoryController(std::shared_ptr<Table> table,
                                       std::shared_ptr<sql::Database> db)
    : AbstractController(table, db) {
  UpdateTable();
};

Result CategoryController::Insert(Category &ct) {
  sql::Statement insert(*db, "INSERT INTO categories (name) VALUES (?)");

  insert.bind(1, ct.name);
  insert.exec();

  ct.id = db->getLastInsertRowid();

  UpdateTable();
  return {true, ""};
}

Result CategoryController::Remove(int64 id) {
  if (!isCategoryExist(*db, id))
    return {false, "Invalid id!"};

  sql::Statement remove(*db, "DELETE FROM categories WHERE id = ?");

  remove.bind(1, id);
  remove.exec();

  UpdateTable();
  return {true, ""};
}

Result CategoryController::Update(int64 id, const std::string &new_name) {
  if (!isCategoryExist(*db, id))
    return {false, "Invalid id!"};

  sql::Statement update(*db, "UPDATE categories SET name = ? WHERE id = ?");

  update.bind(1, new_name);
  update.bind(2, id);
  update.exec();

  UpdateTable();
  return {true, ""};
}

void CategoryController::UpdateTable() {
  sql::Statement query(*db, "SELECT id, name FROM categories");

  table->clear();
  table->push_back({"Id", "Name"});

  while (query.executeStep()) {
    Category ct(query.getColumn(0), query.getColumn(1).getString());

    table->push_back(ct.ToColumn());
  }
}

} // namespace Plutus
