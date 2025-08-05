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
  /// @return Result struct with boolean indicator of succes and std::string of error message
  Result Insert(MonthlyBudget &mb);

  /// @brief Remove budget from database by id
  /// @param category_id Id of category
  /// @param _year Year of period
  /// @param _month Month of period
  /// @return Result struct with boolean indicator of succes and std::string of error message
  Result Remove(int64 category_id, int _year, int _month);

  /// @brief Update existing dubget in database by id
  /// @param category_id Id of category
  /// @param _year Year of period
  /// @param _month Month of period
  /// @param new_budget new budget amount
  /// @return Result struct with boolean indicator of succes and std::string of error message
  Result Update(int64 category_id, int _year, int _month, double new_budget_amount);

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
