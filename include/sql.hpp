#pragma once

#include <string>

#include "mbudget.hpp"
#include "transaction.hpp"
#include "utils.hpp"

namespace Plutus {

/**
 * @brief Creates or open SQLite database with the specified name and initializes
 *        tables and triggers for managing categories and transactions.
 *
 * @param name The name of the database to create.
 * @return sql::Database The created database object.
 */
sql::Database CreateDatabase(const std::string &name);

/**
 * @brief Inserts a new transaction into the transactions table in the database.
 * @note tr.id replaces wiht inserted row id
 *
 * @param db A reference to the SQLite database where the transaction will be inserted.
 * @param tr A reference to the Transaction object containing the data to be inserted.
 */
void InsertTransaction(sql::Database &db, Transaction &tr);

/**
 * @brief Make a sql request and get all transactions from database
 *
 * @param db A reference to the SQLite database
 * @return vector of Transactions or string representation of them
 */
Transactions GetAllTransactions(const sql::Database &db);
Table GetAllTransactionsTable(sql::Database &db);

} // namespace Plutus
