#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

#include "utils.hpp"

namespace sql = SQLite;

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
 * @brief Inserts a new category into the categories table in the database.
 * @note ct.id replaces with inserted row id
 *
 * @param db A reference to the SQLite database where the category will be inserted.
 * @param ct A reference to the Category object containing the data to be inserted.
 */
void InsertCategory(sql::Database &db, Category &ct);

/**
 * @brief Inserts a new transaction into the transactions table in the database.
 * @note tr.id replaces wiht inserted row id
 *
 * @param db A reference to the SQLite database where the transaction will be inserted.
 * @param tr A reference to the Transaction object containing the data to be inserted.
 */
void InsertTransaction(sql::Database &db, Transaction &tr);

} // namespace Plutus
