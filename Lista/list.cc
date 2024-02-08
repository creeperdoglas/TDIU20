#include "List.h"
#include <stdexcept>
#include <vector>
#include <utility>

using namespace std;
// standradkonstruktor
List::List()
{
  last = new Element{};
  first = new Element{};
  last->prev = first;
  first->next = last;
}
// Rensar upp alla allokerade element i listan för att undvika minnesläckage.
List::~List()
{
  if (first != nullptr && last != nullptr)
  {
    Element *temp{first->next};
    while (temp != last)
    {
      temp = temp->next;
      delete temp->prev;
    }
    delete first;
    delete last;
  }
}
// Konstruktor som tar en initializer_list som argument och skapar en lista med elementen i listan.
List::List(initializer_list<int> const &data)
{
  last = new Element{};
  first = new Element{};
  last->prev = first;
  first->next = last;
  for (auto &i : data)
  {
    insert(i);
  }
  // äldre kod, vill testa den innan, tar mindre minne
  // vector<int> vector_data{data};
  // for (unsigned int i{}; i < vector_data.size(); i++)
  // {
  //   insert(vector_data[i]);
  // }
}
// Kopieringskonstruktor
List::List(List const &L)
{
  last = new Element{};
  first = new Element{};
  last->prev = first;
  first->next = last;
  Element *temp{L.first};
  while (temp->next != L.last)
  {
    insert(temp->next->value);
    temp = temp->next;
  }
  // for (int i{}; i < L.size(); i++)
  // {
  //   insert(L[i]);
  // }
}
// Flyttkonstruktor
List::List(List &&L)
{
  last = exchange(L.last, nullptr);
  first = exchange(L.first, nullptr);
}
// Kopieringsoperator
List &List::operator=(List const &L)
{
  if (this != &L)
  {
    Element *temp{L.first};
    while (temp->next != L.last)
    {
      insert(temp->next->value);
      temp = temp->next;
    }
  }
  return *this;
}
// Flyttoperator
List &List::operator=(List &&L)
{
  if (this != &L)
  {
    last = exchange(L.last, nullptr);
    first = exchange(L.first, nullptr);
  }
  return *this;
}
// Returnerar en referens till det element som finns på platsen index i listan.
int List::size() const
{
  int size{};
  Element *temp{first};
  while (temp->next != last)
  {
    size++;
    temp = temp->next;
  }
  return size;
}

// överbelastad operator som returnerar en referens till det element som finns på platsen index i listan.
int &List::operator[](int const index) const
{
  if (index < 0 || index >= size())
  {
    throw out_of_range{"Index out of range"};
  }
  Element *temp{first};
  for (int i{}; i <= index; i++)
  {
    temp = temp->next;
  }
  return temp->value;
}
// Lägger till ett element i listan (insert).
void List::insert(int const N) const
{
  Element *temp{first->next};
  Element *new_element{new Element{N}};
  while (temp != last && temp->value <= N)
  {
    temp = temp->next;
  }
  new_element->next = temp;
  new_element->prev = temp->prev;
  temp->prev->next = new_element;
  temp->prev = new_element;
}

// Tar bort ett element från listan (remove).
void List::remove(int const N) const
{
  Element *temp{first};
  for (int i{}; i < N + 1; i++)
  {
    temp = temp->next;
    if (temp == last)
    {
      throw out_of_range{"Index out of range"};
    }
  }
  temp->next->prev = temp->prev;
  temp->prev->next = temp->next;
  delete temp;
}
// överbelastad operator som skriver ut listan.
ostream &operator<<(ostream &os, List const &L)
{
  List::Element *temp{L.first};
  while (temp->next != L.last)
  {
    temp = temp->next;
    os << temp->value;
    if (temp->next != L.last)
    {
      os << " ";
    }
  }
  return os;
}
// elementkonstruktor
List::Element::Element(int N) : value{N} {}

// begin iterator
List::List_iterator List::begin() const
{
  List_iterator it{};
  it.pos = first->next;
  return it;
}

// end iterator
List::List_iterator List::end() const
{
  List_iterator it{};
  it.pos = last;
  return it;
}
// överbelastning för prefix ++
List::List_iterator &List::List_iterator::operator++()
{
  if (pos == nullptr)
  {
    throw out_of_range{"Unitiated List_iterator"};
  }
  else if (pos->next == nullptr)
  {
    throw out_of_range{"Index out of range"};
  }
  else
  {
    pos = pos->next;
    return *this;
  }
}
List::List_iterator &List::List_iterator::operator=(const List::List_iterator &other)
{
  if (this != &other)
  {
    pos = other.pos;
  }
  return *this;
}
// jämförelseoperator
bool List::List_iterator::operator==(List_iterator const &it) const
{
  return pos == it.pos;
}
bool List::List_iterator::operator!=(List_iterator const &it) const
{
  return pos != it.pos;
}
// överbelastning för dereferensoperatorn
int &List::List_iterator::operator*() const
{
  if (pos == nullptr)
  {
    throw out_of_range{"Unitiated List_iterator"};
  }
  else if (pos->next == nullptr)
  {
    throw out_of_range{"Index out of range"};
  }
  else
  {
    return pos->value;
  }
}
List::List_iterator List::insert(List_iterator position, const int &N)
{
  Element *temp = position.pos;
  Element *new_element = new Element{N};
  while (temp != last && temp->value <= N)
  {
    temp = temp->next;
  }
  new_element->next = temp;
  new_element->prev = temp->prev;
  temp->prev->next = new_element;
  temp->prev = new_element;
  return List_iterator{new_element};
}

// Append an element to the end of the list.
void List::append(int const N) const
{
  Element *new_element = new Element{N};
  new_element->next = last;
  new_element->prev = last->prev;
  last->prev->next = new_element;
  last->prev = new_element;
}

// ...

List *List::sub(const List &indices)
{
  List *sublist = new List;
  int prev_index = -1;
  for (const auto &index : indices)
  {
    if (index < 0 || index >= size())
    {
      throw out_of_range("Index out of range");
    }
    if (index < prev_index)
    {
      throw invalid_argument("Indices not in ascending order");
    }
    sublist->List::append((*this)[index]); // istället för insert
    prev_index = index;
  }
  return sublist;
}