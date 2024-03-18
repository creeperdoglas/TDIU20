#include <iostream>
#include <vector>

class Inventory_Space
{

public:
  Inventory_Space(int *obj = nullptr);
  ~Inventory_Space();
  Inventory_Space(Inventory_Space const &other);
  Inventory_Space(Inventory_Space &&other);

  Inventory_Space &operator=(Inventory_Space const &other) = delete;
  Inventory_Space &operator=(Inventory_Space &&other) = delete;

  Inventory_Space &merge(Inventory_Space &other);
  void print() const;

private:
  int *item{};
};
Inventory_Space::Inventory_Space(int *obj)
    : item{obj}
{
}
Inventory_Space::~Inventory_Space()
{
  delete item;
}
Inventory_Space::Inventory_Space(Inventory_Space const &other)
    : item{new int{*(other.item)}}
{
}

Inventory_Space::Inventory_Space(Inventory_Space &&other)
    : item{other.item}
{
  other.item = nullptr;
}
Inventory_Space &Inventory_Space::merge(Inventory_Space &other)
{
  if (this == &other)
  {
    return *this;
  }
  if (item == nullptr)
  {
    std::swap(item, other.item);
  }
  else if (other.item != nullptr)
  {
    if (*item == *other.item)
    {
      ++*item;
      delete other.item;
      other.item = nullptr;
    }
  }
  return *this;
}
void Inventory_Space::print() const
{
  if (item != nullptr)
  {
    std::cout << *item;
  }
  else
  {
    std::cout << "-";
  }
}

int main()
{
  std::vector<Inventory_Space> v{};

  // Create 8 spaces
  for (unsigned int i{}; i < 8; ++i)
  {
    v.push_back(Inventory_Space{new int{1}});
  }

  for (unsigned int i{0}; i < v.size(); ++i)
  {
    // Merge each space with the next. Empty spaces will "bubble" to
    // the end as each iteration drop the next space into it.
    for (unsigned int j{1}; j < v.size(); ++j)
    {
      v.at(j - 1).merge(v.at(j));
    }

    // Print all spaces after each iteration (one line of output)
    for (unsigned int k{0}; k < v.size(); ++k)
    {
      v.at(k).print();
    }
    std::cout << std::endl;
  }

  return 0;
}