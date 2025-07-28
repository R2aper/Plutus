#include "sql.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>

void usage();
void version();

void print_table(const Table &table) {
  for (auto &t : table) {
    for (auto &c : t)
      std::cout << c << '\t';
    std::cout << std::endl;
  }
}

using namespace Plutus;

int main(void) {
  try {
    auto db = CreateDatabase("financy.db");

    sql::Statement query(db, "SELECT t.id, t.date, t.note, t.amount, t.category_id, c.name "
                             "FROM transactions t JOIN categories c ON t.category_id = c.id");

    Table table = GetAllCategoriesTable(db);
    Table table2 = GetAllTransactionsTable(db);

    print_table(table);
    print_table(table2);

  } catch (const std::exception &e) {
    std::cerr << "Fatal!: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
