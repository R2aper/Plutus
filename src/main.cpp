#include "mbudget.hpp"
#include "sql.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>

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
    auto db = CreateDatabase("financy.db");

    Table table = GetAllCategoriesTable(db);
    Table table2 = GetAllTransactionsTable(db);
    Table table3 = GetAllMonthlyBudgetTable(db);

    print_table(table);
    print_table(table2);
    print_table(table3);

  } catch (const std::exception &e) {
    std::cerr << "Fatal!: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
