#include "controllers/category.hpp"

#include "models/category.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>

namespace sql = SQLite;

namespace Plutus {

CategoryController::CategoryController(std::shared_ptr<Table> table,
                                       std::shared_ptr<sql::Database> db)
    : AbstractController(table, db) {
  UpdateTable();
};

void CategoryController::Insert(Category &ct) {
  sql::Statement insert(*db, "INSERT INTO categories (name) VALUES (?)");

  insert.bind(1, ct.name);
  insert.exec();

  ct.id = db->getLastInsertRowid();
  UpdateTable();
}

void CategoryController::Remove(int64 id) {
  sql::Statement remove(*db, "DELETE FROM categories WHERE id = ?");

  remove.bind(1, id);
  remove.exec();

  UpdateTable();
}

void CategoryController::Update(int64 id, const std::string &new_name) {
  sql::Statement update(*db, "UPDATE categories SET name = ? WHERE id = ?");

  update.bind(1, new_name);
  update.bind(2, id);
  update.exec();

  UpdateTable();
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