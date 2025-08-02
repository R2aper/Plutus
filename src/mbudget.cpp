#include "mbudget.hpp"

namespace Plutus {

// TODO:
MonthlyBudget::MonthlyBudget()
    : id(0), category({1, "untitled"}), year(2025), month(7), budget_amount(0), actual_amount(0.0),
      difference_amount(0) {}

// WTF is this thing so big
MonthlyBudget::MonthlyBudget(int64 _id, const Category &ct, int _year, int _month,
                             double _budget_amount, double _actual_amount,
                             double _difference_amount)
    : id(_id), category(ct), year(_year), month(_month), budget_amount(_budget_amount),
      actual_amount(_actual_amount), difference_amount(_difference_amount) {}

std::vector<std::string> MonthlyBudget::ToColumn() const {
  std::vector<std::string> column;

  column.push_back(std::to_string(id));
  // column.push_back(std::to_string(category.id));
  column.push_back(category.name);
  column.push_back(std::to_string(year) + "-" + std::to_string(month)); //!
  column.push_back(std::to_string(budget_amount));
  column.push_back(std::to_string(actual_amount));
  column.push_back(std::to_string(difference_amount));

  return column;
}

std::ostream &operator<<(std::ostream &os, const MonthlyBudget &mb) {
  os << "Id: " << mb.id
     << std::endl
     // << "Category Id: " << mb.category.id << std::endl
     << "Category name: " << mb.category.name << std::endl
     << "Period:" << mb.year << "-" << mb.month << std::endl
     << "Expected amount" << mb.budget_amount << std::endl
     << "Available amount" << mb.actual_amount << std::endl
     << "Spent amount" << mb.difference_amount << std::endl;

  return os;
}

std::istream &operator>>(std::istream &is, MonthlyBudget &mb) {
  is >> mb.id >> mb.category.id >> mb.year >> mb.month >> mb.budget_amount >> mb.actual_amount >>
      mb.difference_amount;

  return is;
}
}; // namespace Plutus