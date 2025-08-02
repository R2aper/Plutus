#include "sql.hpp"

#include <filesystem>

#include "mbudget.hpp"
#include "transaction.hpp"
#include "utils.hpp"

namespace fs = std::filesystem;

namespace Plutus {

sql::Database CreateDatabase(const std::string &name) {
  sql::Database db(PATH.string() + name, sql::OPEN_CREATE | sql::OPEN_READWRITE);

  // Create table for categories
  db.exec("CREATE TABLE IF NOT EXISTS categories ("
          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
          "name TEXT NOT NULL)");

  // Create table for transactions
  db.exec("CREATE TABLE IF NOT EXISTS transactions ("
          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
          "date TEXT NOT NULL, "
          "note TEXT NOT NULL, "
          "amount REAL NOT NULL, "
          "category_id INTEGER NOT NULL, "
          "FOREIGN KEY (category_id) REFERENCES categories(id))");

  // Create table for monthly budget
  db.exec("CREATE TABLE IF NOT EXISTS monthly_budgets ("
          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
          "category_id INTEGER NOT NULL, "
          "year INTEGER NOT NULL, "
          "month INTEGER NOT NULL, "
          "expected_amount REAL NOT NULL, "
          "available_amount REAL NOT NULL, "
          "spent_amount REAL NOT NULL, "
          "FOREIGN KEY (category_id) REFERENCES categories(id), "
          "UNIQUE(category_id, year, month))");

  return db;
}

} // namespace Plutus
