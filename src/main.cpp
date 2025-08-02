#include "mbudget.hpp"
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

    Category ct;
    ct.name = "Income";
    cc.Insert(ct);

    MonthlyBudget mb;
    mb.year = 2025;
    mb.month = 7;
    mb.budget_amount = 5000.0;
    mb.actual_amount = 6000.0;
    mb.difference_amount = mb.budget_amount - mb.actual_amount;
    mb.category = ct;
    bc.Insert(mb);
    bc.set_period(2025, 7);

    Transaction tr;
    tr.amount = -500.0;
    tr.category = ct;
    tr.date = "2025-07-24";
    tr.note = "Bread";
    tc.Insert(tr);
    tc.set_period(2025, 7);
    tc.set_category_id(ct.id);

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
