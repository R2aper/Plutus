#include "sql.hpp"
#include "utils.hpp"
#include <iostream>
#include <vector>

void usage();
void version();

template <typename T> void print_vec(const std::vector<T> &vec) {
  for (auto &t : vec)
    std::cout << t << std::endl;
}

using namespace Plutus;

int main(void) {
  try {
    auto db = CreateDatabase("financy.db");

    /*
    Category ct = {0, "Grocery", 5000.0, 2000.0, 0.0};
    InsertCategory(db, ct);
    Transaction tr = {0, "2025-07-25", "Bread", -1500.0, ct.id, ""};
    InsertTransaction(db, tr);
    std::cout << "Inserted category:" << ct.id << std::endl
              << "Inserted transaction: " << tr.id << std::endl;
*/
    std::vector<Transaction> trs;
    std::vector<Category> cts;
    sql::Statement query(db, "SELECT t.id, t.date, t.note, t.amount, t.category_id, c.name "
                             "FROM transactions t JOIN categories c ON t.category_id = c.id");

    // Transactions
    while (query.executeStep()) {
      int64 id = query.getColumn(0);
      std::string date = query.getColumn(1);
      std::string note = query.getColumn(2);
      double amount = query.getColumn(3);
      int64 c_id = query.getColumn(4);
      std::string c_name = query.getColumn(5);
      trs.push_back({id, date, note, amount, c_id, c_name});
    }

    sql::Statement query2(
        db, "SELECT id, name, expected_amount, available_amount, spent_amount FROM categories");

    // Categories
    while (query2.executeStep()) {
      int id = query2.getColumn(0);
      std::string name = query2.getColumn(1);
      double expected = query2.getColumn(2);
      double available = query2.getColumn(3);
      double spent = query2.getColumn(4);
      cts.push_back({id, name, expected, available, spent});
    }

    std::cout << std::endl << "Transactins: " << std::endl;
    print_vec(trs);
    std::cout << "Categoris: " << std::endl;
    print_vec(cts);

  } catch (const std::exception &e) {
    std::cerr << "Fatal!: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
