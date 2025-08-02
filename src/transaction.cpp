#include "transaction.hpp"

namespace Plutus {

Transaction::Transaction()
    : id(0), date("2025-07-21"), note(""), amount(0), type(INCOME), category({1, "untitled"}) {}

Transaction::Transaction(int64 _id, const std::string &_date, const std::string &_note,
                         double _amount, const Category &ct)
    : id(_id), date(_date), note(_note), amount(_amount), category(ct) {
  type = (amount < 0) ? EXPENSE : INCOME;
}

std::vector<std::string> Transaction::ToColumn() const {
  std::vector<std::string> column;

  column.push_back(std::to_string(id));
  column.push_back(date);
  column.push_back(note);
  column.push_back(std::to_string(amount));
  //  column.push_back(std::to_string(category.id));
  column.push_back(category.name);

  return column;
}

std::ostream &operator<<(std::ostream &os, const Transaction &tr) {
  os << "Id: " << tr.id << std::endl
     << "Date: " << tr.date << std::endl
     << "Note: " << tr.note << std::endl
     << "Amount: " << tr.amount
     << std::endl
     //   << "Category id: " << tr.category.id << std::endl
     << "Category name: " << tr.category.name;

  return os;
}

std::istream &operator>>(std::istream &is, Transaction &tr) {
  is >> tr.id >> tr.date >> tr.note >> tr.amount >> tr.category.id >> tr.category.name;

  return is;
}

}; // namespace Plutus