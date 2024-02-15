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
  bool sortOnInsert = true;

public:
  List();
  List(bool sortOnInsert);

  ~List();
  List(std::initializer_list<int> const &data);
  void reinitialize(bool sortOnInsert, std::initializer_list<int> const &data = {});
  List(List const &L);
  List(List &&L);

  List &operator=(List const &L);
  List &operator=(List &&L);

  int &operator[](int const index) const;
  void insert(int const N);
  void remove(int const N) const;
  int size() const;
  void append(int const N);
  friend std::ostream &operator<<(std::ostream &os, List const &L);

  class List_iterator
  {
  public:
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
<<<<<<< HEAD
  List *sub(const List &indices);
=======
  List sub(std::initializer_list<int> indices);
>>>>>>> 8c6831d87ed4969c7d5ab888e0aa150d3ebe7497
};
