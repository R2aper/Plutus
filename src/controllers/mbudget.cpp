#include "controllers/mbudget.hpp"
#include "mbudget.hpp"

#include "utils.hpp"

namespace Plutus {

BudgetController::BudgetController(std::shared_ptr<Table> table, std::shared_ptr<sql::Database> db)
    : AbstractController(table, db) {
  set_period(2025, 7); // TODO: current time
  UpdateTable();
}

void BudgetController::set_period(int _year, int _month) noexcept {
  year = _year;
  month = _month;
  UpdateTable();
}

void BudgetController::Insert(MonthlyBudget &mb) {
  sql::Statement insert(
      *db, "INSERT INTO monthly_budgets (category_id, year, month, "
           "expected_amount, available_amount, spent_amount) VALUES (?, ?, ?, ?, ?, ?)");

  insert.bind(1, mb.category.id);
  insert.bind(2, mb.year);
  insert.bind(3, mb.month);
  insert.bind(4, mb.expected_amount);
  insert.bind(5, mb.available_amount);
  insert.bind(6, mb.spent_amount);
  insert.exec();

  mb.id = db->getLastInsertRowid();

  UpdateTable();
}

void BudgetController::Remove(int64 id) {
  sql::Statement remove(*db, "DELETE FROM monthly_budgets WHERE id = ?");

  remove.bind(1, id);
  remove.exec();

  UpdateTable();
}

void BudgetController::Update(int64 id, double new_expected_amount) {
  sql::Statement update(*db, "UPDATE  monthly_budgets SET expected_amount = ? WHERE id = ?");

  update.bind(1, new_expected_amount);
  update.bind(2, id);
  update.exec();

  UpdateTable();
}

void BudgetController::UpdateTable() {
  sql::Statement query(*db,
                       "SELECT cmb.id, c.id, c.name, cmb.year, cmb.month, cmb.expected_amount, "
                       "cmb.available_amount, cmb.spent_amount "
                       "FROM monthly_budgets AS cmb "
                       "JOIN categories AS c ON cmb.category_id = c.id "
                       " WHERE cmb.year = ? AND cmb.month = ?");

  query.bind(1, year);
  query.bind(2, month);

  table->clear();
  table->push_back({"Id", "Category name", "Period", "Expected", "Available", "Spent"});

  while (query.executeStep()) {
    MonthlyBudget mb(query.getColumn(0), {query.getColumn(1), query.getColumn(2).getString()},
                     query.getColumn(3), query.getColumn(4), query.getColumn(5), query.getColumn(6),
                     query.getColumn(7));

    table->push_back(mb.ToColumn());
  }
}

} // namespace Plutus
