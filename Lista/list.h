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

    Element *next{nullptr};
    Element *prev{nullptr};
    int value;
  };
  Element *first, *last;

public:
  List();
  ~List();
  List(std::initializer_list<int> const &data);
  List(List const &L);
  List(List &&L);

  List &operator=(List const &L);
  List &operator=(List &&L);

  int &operator[](int const index) const;
  void insert(int const N) const;
  void remove(int const N) const;
  int size() const;
  friend std::ostream &operator<<(std::ostream &os, List const &L);

  class List_iterator
  {
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = int *;
    using reference = int &;
    using iterator_category = std::bidirectional_iterator_tag;
    friend class List;
    List_iterator &operator=(List_iterator const &);
    List_iterator &operator++();
    bool operator==(List_iterator const &it) const;
    bool operator!=(List_iterator const &it) const;
    int &operator*() const;
    explicit List_iterator(Element *p = nullptr) : pos(p) {}

  private:
    // List_iterator() = default;
    Element *pos; // list_iterator(element *p) var det som tidigare stod, ta en titt senare. detta är en variabel istället för funktion borde bli bättre
  };
  List_iterator begin() const;
  List_iterator end() const;
  List_iterator insert(List_iterator position, const int &N);
  void sub(int index, const List &sublist);
};
