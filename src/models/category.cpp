#include "models/category.hpp"

namespace Plutus {

Category::Category() : id(0), name("") {}

Category::Category(int64 _id, const std::string &_name) : id(_id), name(_name) {}

std::vector<std::string> Category::ToColumn() const {
  std::vector<std::string> column;

  column.push_back(std::to_string(id));
  column.push_back(name);

  return column;
}

std::ostream &operator<<(std::ostream &os, const Category &ct) {
  os << "Id: " << ct.id << std::endl << "Name: " << ct.name << std::endl;

  return os;
}

std::istream &operator>>(std::istream &is, Category &ct) {
  is >> ct.id >> ct.name;

  return is;
}

}; // namespace Plutus