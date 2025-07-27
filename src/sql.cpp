#include <SQLiteCpp/SQLiteCpp.h>
#include <filesystem>

#include "sql.hpp"
#include "utils.hpp"

namespace sql = SQLite;
namespace fs = std::filesystem;

namespace Plutus {

sql::Database CreateDatabase(const std::string &name) {
  sql::Database db(PATH.string() + name, sql::OPEN_CREATE | sql::OPEN_READWRITE);

  // Create table for categories
  db.exec("CREATE TABLE IF NOT EXISTS categories ("
          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
          "name TEXT NOT NULL, "
          "expected_amount REAL NOT NULL, "
          "available_amount REAL NOT NULL, "
          "spent_amount REAL NOT NULL)");

  // Create table for transactions
  db.exec("CREATE TABLE IF NOT EXISTS transactions ("
          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
          "date TEXT NOT NULL, "
          "note TEXT NOT NULL, "
          "amount REAL NOT NULL, "
          "category_id INTEGER NOT NULL, "
          "FOREIGN KEY (category_id) REFERENCES categories(id))");

  db.exec("CREATE TRIGGER IF NOT EXISTS update_category_amounts "
          "AFTER INSERT ON transactions "
          "BEGIN "
          "    UPDATE categories "
          "    SET spent_amount = spent_amount + (CASE WHEN NEW.amount < 0 THEN -NEW.amount ELSE "
          "0 END), "
          "        available_amount = available_amount + NEW.amount "
          "    WHERE id = NEW.category_id; "
          "END;");

  return db;
}

void InsertCategory(sql::Database &db, Category &ct) {
  sql::Statement insert(db, "INSERT INTO categories (name, expected_amount, available_amount, "
                            "spent_amount) VALUES (?, ?, ?, ?)");

  insert.bind(1, ct.name);
  insert.bind(2, ct.expected_amount);
  insert.bind(3, ct.available_amount);
  insert.bind(4, ct.spent_amount);
  insert.exec();

  ct.id = db.getLastInsertRowid();
}

void InsertTransaction(sql::Database &db, Transaction &tr) {
  sql::Statement insert(
      db, "INSERT INTO transactions (date, note, amount, category_id) VALUES (?, ?, ?, ?)");

  insert.bind(1, tr.date);
  insert.bind(2, tr.note);
  insert.bind(3, tr.amount);
  insert.bind(4, tr.category_id);
  insert.exec();

  tr.id = db.getLastInsertRowid();
}

} // namespace Plutus
