#include "models/mbudget.hpp"
#include "sql.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>

#include "controllers/category.hpp"
#include "controllers/mbudget.hpp"
#include "controllers/transaction.hpp"

using namespace Plutus;

//

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

    Category ct(0, "Grocery");
    Result a = cc.Insert(ct);
    if (!a) {
      std::cerr << a.error_msg << '\n';
      return 1;
    }

    MonthlyBudget mb(0, ct, 2025, 7, 5000.0, 0.0, 0.0);
    bc.set_period(2025, 7);
    a = bc.Insert(mb);

    if (!a) {
      std::cerr << a.error_msg << '\n';
      return 1;
    }
    Transaction tr(0, "2025-07-21", "Bread", -500.0, ct);
    tc.set_category_id(ct.id);
    tc.set_period(2025, 7);
    a = tc.Insert(tr);
    if (!a) {
      std::cerr << a.error_msg << '\n';
      return 1;
    }
    bc.UpdateTable();

    std::cout << "Categories:" << '\n';
    print_table(*CategoriesTable);
    std::cout << "Budgets:" << '\n';
    print_table(*BudgetsTable);
    std::cout << "Transactions:" << '\n';
    print_table(*TransactionTable);

  } catch (const std::exception &e) {
    std::cerr << "Fatal!: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
