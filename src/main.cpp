#include "mbudget.hpp"
#include "sql.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>

#include "controllers/category.hpp"
#include "controllers/mbudget.hpp"

using namespace Plutus;

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

    CategoryController cc(CategoriesTable, db);
    BudgetController bc(BudgetsTable, db);

    std::cout << "Categories:" << '\n';
    print_table(*CategoriesTable);
    std::cout << "Budgets:" << '\n';
    print_table(*BudgetsTable);

    Category ct;
    ct.name = "Grocery";
    cc.Insert(ct);

    bc.set_period(2025, 7);
    MonthlyBudget mb;
    mb.category.id = ct.id;
    mb.month = 7;
    mb.year = 2025;
    mb.expected_amount = 500.0;
    mb.spent_amount = 0.0;
    mb.available_amount = mb.expected_amount - mb.spent_amount;

    bc.Insert(mb);

    std::cout << "Categories:" << '\n';
    print_table(*CategoriesTable);
    std::cout << "Budgets:" << '\n';
    print_table(*BudgetsTable);

  } catch (const std::exception &e) {
    std::cerr << "Fatal!: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
