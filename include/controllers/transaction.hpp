#pragma once

#include "models/category.hpp"
#include "controllers/abstract.hpp"
#include "models/transaction.hpp"
#include "utils.hpp"

namespace Plutus {

struct Transaction;
struct Category;

class TransactionController : public AbstractController {
public:
  explicit TransactionController(std::shared_ptr<Table> table, std::shared_ptr<sql::Database> db);

  /// @brief Insert Transaction into 'transactions' table of database
  /// @param mb New transaction
  void Insert(Transaction &tr);

  /// @brief Remove Transaction from database by id
  /// @param id Id of Transaction to remove
  void Remove(int64 id);

  /// @brief Update existing Transaction in database by id
  /// @param id Id of  Transaction to update
  /// @param new_date New date of transaction
  /// @param new_note New note of transaction
  /// @param new_amount New amount of transaction
  /// @param new_category_id New category id of transaction
  void Update(int64 id, const std::string &new_date, const std::string &new_note, double new_amount,
              int64 new_category_id);

  /// @brief set period of transaction(table will fetch all transactions for this peruid)
  void set_period(int _year, int _month);

  /// @brief set id of category to show
  void set_category_id(int64 id);

  /// @brief Fetch table with database
  void UpdateTable() override;

private:
  // Period of transaction(We don't need to print all of them, just of given period)
  int year;
  int month;
  int64 category_id; // Id of current showing category
};

} // namespace Plutus
