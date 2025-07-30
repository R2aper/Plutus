#include "transaction.hpp"

namespace Plutus {

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

std::istream &operator>>(std::istream &is, Transaction &tr) {
  is >> tr.id >> tr.date >> tr.note >> tr.amount >> tr.category_id >> tr.category;
  return is;
}

}; // namespace Plutus