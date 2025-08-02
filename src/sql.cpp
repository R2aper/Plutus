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
