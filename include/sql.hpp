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

} // namespace Plutus
