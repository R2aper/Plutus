#include "controllers/mbudget.hpp"
#include "models/mbudget.hpp"

#include "sql.hpp"
#include "utils.hpp"

namespace Plutus {

BudgetController::BudgetController(std::shared_ptr<Table> table, std::shared_ptr<sql::Database> db)
    : AbstractController(table, db) {
  set_period(2025, 7); // TODO: current time

  UpdateTable();
}

void BudgetController::set_period(int _year, int _month) {
  year = _year;
  month = _month;

  UpdateTable();
}

Result BudgetController::Insert(MonthlyBudget &mb) {
  if (!isCategoryExist(*db, mb.category.id))
    return {false, "Invalid category!"};
  if (isBudgetExist(*db, mb.category.id, mb.year, mb.month))
    return {false, "Budget for this period already exist!"};

  sql::Statement insert(*db, "INSERT INTO monthly_budgets (category_id, year, month, "
                             "budget, difference, actual) VALUES (?, ?, ?, ?, ?, ?)");

  insert.bind(1, mb.category.id);
  insert.bind(2, mb.year);
  insert.bind(3, mb.month);
  insert.bind(4, mb.budget_amount);
  insert.bind(5, mb.difference_amount);
  insert.bind(6, mb.actual_amount);
  insert.exec();

  mb.id = db->getLastInsertRowid();

  UpdateTable();
  return {true, ""};
}

Result BudgetController::Remove(int64 category_id, int _year, int _month) {
  if (!isBudgetExist(*db, category_id, _year, _month))
    return {false, "No budget to remove!"};

  sql::Statement remove(
      *db, "DELETE FROM monthly_budgets WHERE category_id = ? AND year = ? AND month = ?");

  remove.bind(1, category_id);
  remove.bind(2, _year);
  remove.bind(3, _month);
  remove.exec();

  UpdateTable();
  return {true, ""};
}

Result BudgetController::Update(int64 category_id, int _year, int _month, double new_budget) {
  if (!isBudgetExist(*db, category_id, _year, _month))
    return {false, "No budget to update"};

  sql::Statement update(
      *db,
      "UPDATE monthly_budgets SET budget = ? WHERE category_id = ? AND year = ? AND month = ?");

  update.bind(1, new_budget);
  update.bind(2, category_id);
  update.bind(3, _year);
  update.bind(4, _month);
  update.exec();

  UpdateTable();
  return {true, ""};
}

void BudgetController::UpdateTable() {
  sql::Statement query(*db, "SELECT cmb.id, c.id, c.name, cmb.year, cmb.month, cmb.budget, "
                            "cmb.actual, cmb.difference "
                            "FROM monthly_budgets AS cmb "
                            "JOIN categories AS c ON cmb.category_id = c.id "
                            " WHERE cmb.year = ? AND cmb.month = ?");

  query.bind(1, year);
  query.bind(2, month);

  table->clear();
  table->push_back({"Id", "Category name", "Period", "Budget", "Actual", "Difference"});

  while (query.executeStep()) {
    MonthlyBudget mb(query.getColumn(0), {query.getColumn(1), query.getColumn(2).getString()},
                     query.getColumn(3), query.getColumn(4), query.getColumn(5), query.getColumn(6),
                     query.getColumn(7));

    table->push_back(mb.ToColumn());
  }
}

} // namespace Plutus
