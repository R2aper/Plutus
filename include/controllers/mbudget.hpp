#pragma once

#include "controllers/abstract.hpp"
#include "models/mbudget.hpp"
#include "utils.hpp"

namespace Plutus {

struct MonthlyBudget;

class BudgetController : public AbstractController {
public:
  explicit BudgetController(std::shared_ptr<Table> table, std::shared_ptr<sql::Database> db);

  /// @brief Insert new budget into 'monthly_budgets' table of database
  /// @param mb New monthly budget
  void Insert(MonthlyBudget &mb);

  /// @brief Remove budget from database by id
  /// @param id Id of budget to remove
  void Remove(int64 id);

  /// @brief Update existing dubget in database by id
  /// @param id Id of budget to update
  /// @param new_budget new budget amount
  void Update(int64 id, double new_budget_amount);

  /// @brief Set period of budget(table will fetch budgets for this peruid)
  void set_period(int _year, int _month);

  /// @brief Fetch table with database
  void UpdateTable() override;

private:
  // Period of budgets(We don't need to print all of them, just of given period)
  int year;
  int month;
};

} // namespace Plutus
