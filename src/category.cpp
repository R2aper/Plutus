#include "category.hpp"

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

std::istream &operator>>(std::istream &is, Category &ct) {
  is >> ct.id >> ct.name >> ct.expected_amount >> ct.available_amount >> ct.spent_amount;

  return is;
}

}; // namespace Plutus