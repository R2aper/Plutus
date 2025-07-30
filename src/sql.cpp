#include <SQLiteCpp/SQLiteCpp.h>
#include <filesystem>

#include "category.hpp"
#include "sql.hpp"
#include "transaction.hpp"
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

  // Trigger after create in transactions
  // Update category fields
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
  insert.bind(4, tr.category.id);
  insert.exec();

  tr.id = db.getLastInsertRowid();
}

Categories GetAllCategories(const sql::Database &db) {
  Categories cts;
  sql::Statement query(
      db, "SELECT id, name, expected_amount, available_amount, spent_amount FROM categories");

  while (query.executeStep()) {
    Category ct;
    ct.id = query.getColumn(0);
    ct.name = query.getColumn(1).getString();
    ct.expected_amount = query.getColumn(2);
    ct.available_amount = query.getColumn(3);
    ct.spent_amount = query.getColumn(4);

    cts.push_back(ct);
  }

  return cts;
}

Table GetAllCategoriesTable(const sql::Database &db) {
  Table table;
  sql::Statement query(
      db, "SELECT id, name, expected_amount, available_amount, spent_amount FROM categories");

  table.push_back({"Id", "Name", "Expected", "Available", "Spent"});

  while (query.executeStep()) {
    Category ct;
    ct.id = query.getColumn(0);
    ct.name = query.getColumn(1).getString();
    ct.expected_amount = query.getColumn(2);
    ct.available_amount = query.getColumn(3);
    ct.spent_amount = query.getColumn(4);

    table.push_back(ct.ToColumn());
  }

  return table;
}

Transactions GetAllTransactions(const sql::Database &db) {
  Transactions trs;
  sql::Statement query(db, "SELECT t.id, t.date, t.note, t.amount, t.category_id, c.name "
                           "FROM transactions t JOIN categories c ON t.category_id = c.id");

  while (query.executeStep()) {
    Transaction tr;
    tr.id = query.getColumn(0);
    tr.date = query.getColumn(1).getString();
    tr.note = query.getColumn(2).getString();
    tr.amount = query.getColumn(3);
    tr.category.id = query.getColumn(4);
    tr.category.name = query.getColumn(5).getString();

    trs.push_back(tr);
  }

  return trs;
}

Table GetAllTransactionsTable(sql::Database &db) {
  Table table;
  sql::Statement query(db, "SELECT t.id, t.date, t.note, t.amount, t.category_id, c.name "
                           "FROM transactions t JOIN categories c ON t.category_id = c.id");

  table.push_back({"Id", "Date", "Note", "Amount", "Name"});

  while (query.executeStep()) {
    Transaction tr;
    tr.id = query.getColumn(0);
    tr.date = query.getColumn(1).getString();
    tr.note = query.getColumn(2).getString();
    tr.amount = query.getColumn(3);
    tr.category.id = query.getColumn(4);
    tr.category.name = query.getColumn(5).getString();

    table.push_back(tr.ToColumn());
  }

  return table;
}

} // namespace Plutus
