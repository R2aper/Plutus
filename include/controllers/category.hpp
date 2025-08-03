#pragma once

#include "controllers/abstract.hpp"

#include "models/category.hpp"
#include "utils.hpp"

namespace Plutus {

struct Category;

class CategoryController : public AbstractController {
public:
  explicit CategoryController(std::shared_ptr<Table> table, std::shared_ptr<sql::Database> db);

  /// @brief Insert Category into 'categoreis' table of database
  /// @param ct New category
  void Insert(Category &ct);

  /// @brief Remove Category from database by id
  /// @param id Id of category to remove
  void Remove(int64 id);

  /// @brief Update existing Category in database by id
  /// @param id Id of category to update
  /// @param new_name New name of Category
  void Update(int64 id, const std::string &new_name);

  /// @brief Fetch table with database
  void UpdateTable() override;
};

} // namespace Plutus