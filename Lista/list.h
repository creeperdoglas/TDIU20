#pragma once
#include <iostream>
#include <initializer_list>

class List
{
private:
  class Element
  {
  public:
    Element() = default;
    Element(int n);
    ~Element() = default;
    Element(Element const &) = delete;
    Element(Element &&) = delete;
    Element operator=(Element const &) = delete;
    Element operator=(Element &&) = delete;
  }
};
