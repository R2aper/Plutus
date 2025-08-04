#pragma once

#include <string>

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

std::string getNameById(const sql::Database &db, int64 category_id);

bool isCategoryExist(const sql::Database &db, int64 category_id);
bool isBudgetExist(const sql::Database &db, int64 category_id, int year, int month);
bool isTransactionExist(const sql::Database &db, int64 id);

} // namespace Plutus
