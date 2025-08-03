#include "sql.hpp"

#include <filesystem>

#include "mbudget.hpp"
#include "transaction.hpp"
#include "utils.hpp"

namespace fs = std::filesystem;

namespace Plutus {

static inline void trigger_after_insert_transaction(sql::Database &db) {
  db.exec("CREATE TRIGGER IF NOT EXISTS insert_transaction_trigger "
          "AFTER INSERT ON transactions "
          "BEGIN "
          "    UPDATE monthly_budgets "
          "    SET actual = actual + (-NEW.amount), "
          "    difference = difference + NEW.amount "
          "    WHERE category_id = NEW.category_id "
          "    AND year = strftime('%Y', NEW.date) "
          "    AND month = strftime('%m', NEW.date); "
          "END;");
}

void inline trigger_after_insert_transaction_create_budget(sql::Database &db) {
  db.exec("CREATE TRIGGER IF NOT EXISTS insert_transaction_create_budget_trigger "
          "AFTER INSERT ON transactions "
          "FOR EACH ROW "
          "WHEN NOT EXISTS ("
          "    SELECT 1 FROM monthly_budgets "
          "    WHERE category_id = NEW.category_id "
          "    AND year = strftime('%Y', NEW.date) "
          "    AND month = strftime('%m', NEW.date) "
          ") "
          "BEGIN "
          "    INSERT INTO monthly_budgets (category_id, year, month, budget, "
          "actual, difference) "
          "    VALUES (NEW.category_id, strftime('%Y', NEW.date), strftime('%m', NEW.date), 0.0, "
          "0.0, 0.0); "
          "    UPDATE monthly_budgets "
          "    SET actual = actual + (-NEW.amount) "
          "        difference = difference + NEW.amount "
          "    WHERE category_id = NEW.category_id "
          "    AND year = strftime('%Y', NEW.date) "
          "    AND month = strftime('%m', NEW.date); "
          "END;");
}

static inline void trigger_after_delete_transaction(sql::Database &db) {
  db.exec("CREATE TRIGGER IF NOT EXISTS delete_transaction_trigger "
          "AFTER DELETE ON transactions "
          "FOR EACH ROW "
          "BEGIN "
          "    UPDATE monthly_budgets "
          "    SET actual = actual - (-OLD.amount), "
          "    difference = difference - OLD.amount "

          "    WHERE category_id = OLD.category_id "
          "    AND year = strftime('%Y', OLD.date) "
          "    AND month = strftime('%m', OLD.date); "
          "END;");
}

static inline void trigger_after_delete_category(sql::Database &db) {
  db.exec("CREATE TRIGGER IF NOT EXISTS delete_category_trigger "
          "AFTER DELETE ON categories "
          "FOR EACH ROW "
          "BEGIN "
          "    DELETE FROM monthly_budgets "
          "    WHERE category_id = OLD.id; "

          "    UPDATE transactions"
          "    SET category_id = (SELECT id FROM categories WHERE name = 'untitled') "
          "    WHERE category_id = OLD.id; "
          "END;");
}

static inline void trigger_after_delete_budget(sql::Database &db) {
  db.exec("CREATE TRIGGER IF NOT EXISTS delete_monthly_budget_trigger "
          "AFTER DELETE ON monthly_budgets "
          "FOR EACH ROW "
          "BEGIN "
          "    UPDATE transactions "
          "    SET category_id = (SELECT id FROM categories WHERE name = 'untitled') "
          "    WHERE category_id = OLD.category_id "
          "    AND strftime('%Y', date) = OLD.year "
          "    AND strftime('%m', date) = OLD.month; "
          "END;");
}

static inline void trigger_after_update_transaction(sql::Database &db) {
  db.exec(
      "CREATE TRIGGER IF NOT EXISTS update_transaction_trigger "
      "AFTER UPDATE ON transactions "
      "FOR EACH ROW "
      "WHEN OLD.amount <> NEW.amount OR OLD.date <> NEW.date OR OLD.category_id <> NEW.category_id "
      "BEGIN "
      "    UPDATE monthly_budgets "
      "    SET actual = actual - (-OLD.amount), "
      "    difference = difference - OLD.amount "
      "    WHERE category_id = OLD.category_id "
      "    AND year = strftime('%Y', OLD.date) "
      "    AND month = strftime('%m', OLD.date); "

      "    UPDATE monthly_budgets "
      "    SET actual = actual +  -NEW.amount, "
      "    difference = difference + NEW.amount"
      "    WHERE category_id = NEW.category_id "
      "    AND year = strftime('%Y', NEW.date) "
      "    AND month = strftime('%m', NEW.date); "
      "END;");
}

static inline void trigger_after_update_budget(sql::Database &db) {
  db.exec("CREATE TRIGGER IF NOT EXISTS update_budget_trigger "
          "AFTER UPDATE OF budget ON monthly_budgets "
          "FOR EACH ROW "
          "WHEN OLD.budget <> NEW.budget "
          "BEGIN "
          "    UPDATE monthly_budgets "
          "SET difference = difference + (NEW.budget - OLD.budget) "
          " WHERE id = NEW.id; "
          "END;");
}

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
          "year INTEGER NOT NULL CHECK(year >= 0), "
          "month INTEGER NOT NULL CHECK(month > 0 AND month <= 12), "
          "budget REAL NOT NULL, "
          "actual REAL NOT NULL, "
          "difference REAL NOT NULL, "
          "FOREIGN KEY (category_id) REFERENCES categories(id), "

          "UNIQUE(category_id, year, month))");

  db.exec("INSERT INTO categories (name) SELECT 'Untitled' WHERE NOT EXISTS (SELECT 1 FROM "
          "categories WHERE name = 'Untitled')");

  trigger_after_insert_transaction_create_budget(db);
  trigger_after_insert_transaction(db);
  trigger_after_delete_transaction(db);
  trigger_after_delete_category(db);
  trigger_after_delete_budget(db);
  trigger_after_update_transaction(db);
  trigger_after_update_budget(db);

  return db;
}

} // namespace Plutus
