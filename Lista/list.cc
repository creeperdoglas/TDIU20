#include "List.h"
#include <stdexcept>
#include <vector>

using namespace std;

List::List()
{
  last = new Element{};
  first = new Element{};
  last->prev = first;
  first->next = last;
}
