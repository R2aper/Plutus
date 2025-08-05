#include "controllers/transaction.hpp"

#include "models/transaction.hpp"
#include "sql.hpp"
#include "utils.hpp"

namespace Plutus {

TransactionController::TransactionController(std::shared_ptr<Table> table,
                                             std::shared_ptr<sql::Database> db)
    : AbstractController(table, db) {
  set_period(2025, 8); // TODO: current time
  set_category_id(1);

  UpdateTable();
}

void TransactionController::set_period(int _year, int _month) {
  year = _year;
  month = _month;

  UpdateTable();
}

void TransactionController::set_category_id(int64 id) {
  category_id = id;

  UpdateTable();
}

// TODO: add category by name
Result TransactionController::Insert(Transaction &tr) {
  if (!isCategoryExist(*db, tr.category.id))
    return {false, "Invalid category!"};

  sql::Statement insert(
      *db, "INSERT INTO transactions (date, note, amount, category_id) VALUES (?, ?, ?, ?)");

  insert.bind(1, tr.date);
  insert.bind(2, tr.note);
  insert.bind(3, tr.amount);
  insert.bind(4, tr.category.id);
  insert.exec();

  tr.id = db->getLastInsertRowid();

  UpdateTable();
  return {true, ""};
}

Result TransactionController::Remove(int64 id) {
  if (!isTransactionExist(*db, id))
    return {false, "Invalid id!"};

  sql::Statement remove(*db, "DELETE FROM transactions WHERE id = ?");

  remove.bind(1, id);
  remove.exec();

  UpdateTable();
  return {true, ""};
}

Result TransactionController::Update(int64 id, const std::string &new_date,
                                     const std::string &new_note, double new_amount,
                                     int64 new_category_id) {
  if (!isTransactionExist(*db, id))
    return {false, "Invalid id!"};
  if (!isCategoryExist(*db, new_category_id))
    return {false, "Invalid category!"};

  sql::Statement update(
      *db, "UPDATE transactions SET date = ?, note = ?, amount = ?, category_id = ? WHERE id = ?");

  update.bind(1, new_date);
  update.bind(2, new_note);
  update.bind(3, new_amount);
  update.bind(4, new_category_id);
  update.bind(5, id);
  update.exec();

  UpdateTable();
  return {true, ""};
}

void TransactionController::UpdateTable() {
  sql::Statement query(*db, "SELECT t.id, t.date, t.note, t.amount, t.category_id, c.name "
                            "FROM transactions t JOIN categories c ON t.category_id = c.id");

  table->clear();
  table->push_back({"Id", "Date", "Note", "Amount", "Category name"});

  while (query.executeStep()) {
    Transaction tr(query.getColumn(0), query.getColumn(1).getString(),
                   query.getColumn(2).getString(), query.getColumn(3),
                   {query.getColumn(4), query.getColumn(5).getString()});

    table->push_back(tr.ToColumn());
  }
}

} // namespace Plutus
