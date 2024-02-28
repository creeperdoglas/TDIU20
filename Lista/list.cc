#include "list.h"
#include <stdexcept>
#include <vector>
#include <utility>
#include <sstream>
// Information om komplettering:
//   Kompletteringen kan gälla hela filen och alla filer i labben,
//   så får ni komplettering på en sak, kan samma sak förekomma på
//   fler ställen utan att jag skrivit det.
//
//   Komplettering lämnas in via sendlab efter senast en (1) vecka
//
//   Har ni frågor om kompletteringen kan ni maila mig på:
//   Malte.Nilsson@liu.se

// Koden kompilerade inte pga ändring av filnamn (fixade det)
/// tack så mycket, måste ha råkat skickat in fel verision :/

// Komplettering: Koden kompilerar med varningar.
/// fixat, glömde bort att kompilera med kursens kompileringsflaggor
/// blev många varningat, kan dock ha ändrat vissa saker i onödan men inga varningar nu och alla testfall går igenom

// Komplettering: friend för utströmmen är inte en okej lösning i den här kursen.
/// fixade, däremot fixar jag inte friend för iterator då det skulle krävas extra arbete för att göra det utan att använda friend, för något som ändå inte behövs i uppgiften
/// hoppas det är okej
/// skapade en to_string metod för att kunna skriva ut listan utan att behöva använda friend, skulla nog kunna ha använt mig utav iteratorn faktist men antar att eftersom det visade
/// sig att de inte var nödvändigt så använder jag mig inte av den

// Hur kommer det sig att ni har implementerat en List_Iterator?
// svara vid komplettering:
/// även fast i den här uppgiften en list_Iterator inte är nödvändig för det listan ska göra så började vi med att implementera det i början för att kunna
/// iterera genom listan, detta hände på grund av att jag läste igenom lite för snabbt "Däremot gör en sentinel att implementationen kan förenklas genom att specialfall utgår. Den ger även fördel när en bidirectional iterator ska skapas."
/// antog att detta betydde att vi förväntades att implementera en iterator, däremot när jag insåg att det inte var nödvändigt så lät jag det vara då den redan i stort
/// sett var klar, så skrev lite testfall till den för att visa att den funkar. tänkte att om något så visar det att vi har förstått hur det fungerar, däremot så visar det även hur dåligt jag läser igenom intruktioner :/
/// notera att på grund av detta så är den inte bidirectional, det skulle krävas en operator -- för det.
using namespace std;
// standradkonstruktor
List::List() : first(new Element()), last(new Element())
{
  first->next = last;
  last->prev = first;
}

// Konstruktor som tar en initializer_list som argument och skapar en lista med elementen i listan.
List::List(std::initializer_list<int> const &data) : List()
{
  last->prev = first;
  first->next = last;
  for (auto &i : data)
  {
    insert(i);
  }
}

// Copy constructor
List::List(List const &L) : List()
{
  last->prev = first;
  first->next = last;
  Element *temp{L.first};
  while (temp->next != L.last)
  {
    insert(temp->next->value);
    temp = temp->next;
  }
}

// Move constructor
List::List(List &&L) : first(std::exchange(L.first, nullptr)), last(std::exchange(L.last, nullptr)) {}

// Destructor
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

// Copy assignment operator
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

// Move assignment operator
List &List::operator=(List &&L) noexcept
{
  if (this != &L)
  {
    last = exchange(L.last, nullptr);
    first = exchange(L.first, nullptr);
  }
  return *this;
}

// Insert an element i sorterad ordning
void List::insert(int N)
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

// Remove
void List::remove(int N)
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

// Returnerar en referens till det element som finns på platsen index i listan.
int List::size() const
{
  int count = 0;
  Element *curr = first->next;
  while (curr != last)
  {
    ++count;
    curr = curr->next;
  }
  return count;
}

// överbelastad operator som returnerar en referens till det element som finns på platsen index i listan.
int &List::operator[](int const index) const
{
  if (index < 0 || index >= size())
  {
    throw std::out_of_range("Index out of range");
  }
  Element *curr = first->next;
  for (int i = 0; i < index; ++i)
  {
    curr = curr->next;
  }
  return curr->value;
}

// konvertera lista till string
std::string List::to_string() const
{
  std::stringstream ss;
  for (Element *curr = first->next; curr != last; curr = curr->next)
  {
    ss << curr->value;
    if (curr->next != last)
      ss << " ";
  }
  return ss.str();
}
// List::Element::Element(int n) : value(n), next(nullptr), prev(nullptr) {}

// Overload << operator
std::ostream &operator<<(std::ostream &os, List const &L)
{
  os << L.to_string();
  return os;
}
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

// Append
void List::append(int N)
{
  Element *newElement = new Element{N};
  newElement->next = last;
  newElement->prev = last->prev;
  last->prev->next = newElement;
  last->prev = newElement;
}

// ...
List List::sub(std::initializer_list<int> indices)
{
  List sublist;
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
    sublist.append((*this)[index]); // istället för insert
    prev_index = index;
  }
  return sublist;
}