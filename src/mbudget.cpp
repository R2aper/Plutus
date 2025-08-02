#include "mbudget.hpp"

namespace Plutus {

// TODO:
MonthlyBudget::MonthlyBudget()
    : id(0), category({1, "untitled"}), year(2025), month(7), expected_amount(0),
      available_amount(0), spent_amount(0.0) {}

// WTF is this thing so big
MonthlyBudget::MonthlyBudget(int64 _id, const Category &ct, int _year, int _month,
                             double _expected_amount, double _available_amount,
                             double _spent_amount)
    : id(_id), category(ct), year(_year), month(_month), expected_amount(_expected_amount),
      available_amount(_available_amount), spent_amount(_spent_amount) {}

std::vector<std::string> MonthlyBudget::ToColumn() const {
  std::vector<std::string> column;

  column.push_back(std::to_string(id));
  // column.push_back(std::to_string(category.id));
  column.push_back(category.name);
  column.push_back(std::to_string(year) + "-" + std::to_string(month)); //!
  column.push_back(std::to_string(expected_amount));
  column.push_back(std::to_string(available_amount));
  column.push_back(std::to_string(spent_amount));

  return column;
}

std::ostream &operator<<(std::ostream &os, const MonthlyBudget &mb) {
  os << "Id: " << mb.id
     << std::endl
     // << "Category Id: " << mb.category.id << std::endl
     << "Category name: " << mb.category.name << std::endl
     << "Period:" << mb.year << "-" << mb.month << std::endl
     << "Expected amount" << mb.expected_amount << std::endl
     << "Available amount" << mb.available_amount << std::endl
     << "Spent amount" << mb.spent_amount << std::endl;

  return os;
}

std::istream &operator>>(std::istream &is, MonthlyBudget &mb) {
  is >> mb.id >> mb.category.id >> mb.year >> mb.month >> mb.expected_amount >>
      mb.available_amount >> mb.spent_amount;

  return is;
}
}; // namespace Plutus