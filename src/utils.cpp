#include <string>
#include <vector>

#include "utils.hpp"

namespace Plutus {

std::vector<std::string> Category::ToColumn() const {
  std::vector<std::string> column;

  column.push_back(std::to_string(id));
  column.push_back(name);
  column.push_back(std::to_string(expected_amount));
  column.push_back(std::to_string(available_amount));
  column.push_back(std::to_string(spent_amount));

  return column;
}

std::ostream &operator<<(std::ostream &os, const Category &ct) {
  os << "Id: " << ct.id << std::endl
     << "Name: " << ct.name << std::endl
     << "Expected ammount: " << ct.expected_amount << std::endl
     << "Available amount: " << ct.available_amount << std::endl
     << "Spent amount: " << ct.spent_amount;
  return os;
}

std::vector<std::string> Transaction::ToColumn() const {
  std::vector<std::string> column;

  column.push_back(std::to_string(id));
  column.push_back(date);
  column.push_back(note);
  column.push_back(std::to_string(amount));
  // column.push_back(std::to_string(category_id));
  column.push_back(category);

  return column;
}

std::ostream &operator<<(std::ostream &os, const Transaction &tr) {
  os << "Id: " << tr.id << std::endl
     << "Date: " << tr.date << std::endl
     << "Note: " << tr.note << std::endl
     << "Amount: " << tr.amount << std::endl
     << "Category id: " << tr.category_id << std::endl
     << "Category name: " << tr.category;
  return os;
}

}; // namespace Plutus
