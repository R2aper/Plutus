#include "mbudget.hpp"
#include "sql.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>

#include "controllers/category.hpp"

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

    CategoryController cc(CategoriesTable, db);

    std::cout << "Categories:" << '\n';
    print_table(*CategoriesTable);

    Category ct;
    ct.name = "Grocery";
    cc.Insert(ct);

    std::cout << "Categories:" << '\n';
    print_table(*CategoriesTable);

  } catch (const std::exception &e) {
    std::cerr << "Fatal!: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
