#include "models/mbudget.hpp"
#include "sql.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>

#include "controllers/category.hpp"
#include "controllers/mbudget.hpp"
#include "controllers/transaction.hpp"

using namespace Plutus;

// trigger update_budget
// Проверка на валидность категорий и бюджета

void usage();
void version();

void print_table(const Table &table) {
  for (auto &t : table) {
    for (auto &c : t)
      std::cout << c << '\t';
    std::cout << std::endl;
  }
}

int main(void) {
  try {
    std::shared_ptr<sql::Database> db =
        std::make_shared<sql::Database>(CreateDatabase("financy.db"));

    std::shared_ptr<Table> CategoriesTable = std::make_shared<Table>();
    std::shared_ptr<Table> BudgetsTable = std::make_shared<Table>();
    std::shared_ptr<Table> TransactionTable = std::make_shared<Table>();

    CategoryController cc(CategoriesTable, db);
    BudgetController bc(BudgetsTable, db);
    TransactionController tc(TransactionTable, db);

    Category ct;
    ct.name = "Grocery";
    cc.Insert(ct);

    MonthlyBudget mb(0, ct, 2025, 7, 5000.0, 0, 5000.0);
    bc.Insert(mb);
    bc.set_period(2025, 7);

    Transaction tr(0, "2025-07-24", "Bread", -500.0, ct);
    tc.Insert(tr);
    tc.set_period(2025, 7);
    tc.set_category_id(ct.id);

    std::cout << "Categories:" << '\n';
    print_table(*CategoriesTable);
    std::cout << "Budgets:" << '\n';
    print_table(*BudgetsTable);
    std::cout << "Transactions:" << '\n';
    print_table(*TransactionTable);
    std::cout << std::endl;

    Category ct2(0, "Income");
    cc.Insert(ct2);

    MonthlyBudget mb2(0, ct2, 2025, 7, 10000.0, 0, 10000.0);
    bc.Insert(mb2);

    Transaction tr2(0, "2025-07-01", "Salary", 5000.0, ct2);
    tc.Insert(tr2);
    tc.set_category_id(ct2.id);
    bc.UpdateTable();

    std::cout << "Categories:" << '\n';
    print_table(*CategoriesTable);
    std::cout << "Budgets:" << '\n';
    print_table(*BudgetsTable);
    std::cout << "Transactions:" << '\n';
    print_table(*TransactionTable);
    std::cout << std::endl;

  } catch (const std::exception &e) {
    std::cerr << "Fatal!: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
