#pragma once // endast kompileras en gång
#include <iostream>
#include <string>
class Time
{
public:
  Time() = default;
  Time(int const h, int const m, int const s);
  bool check_for_invalid_input(int const h, int const m, int const s);
  Time(std::string const &t);

  int get_hour() const;
  int get_minute() const;
  int get_second() const;

  bool is_am() const;
  std::string to_string(const bool = false) const; // till att byta mellan 24 och 12 timmars
  operator std::string() const;                    // konvertera Time till sträng

  Time operator+(int const n) const; // Lägger till N sekunder
  Time operator++(int);              // post increment
  Time &operator++();                // efter läst på lite så har jag kommit fram till att det här behövs, detta är en "prefix verision" , fortarande lite osäker men testat fram och funkar

  Time operator-(int const n) const; // tar bort sekunder
  Time operator--(int);              // post decrement
  Time &operator--();

  // jämförelser
  bool operator==(Time const &t) const;
  bool operator!=(Time const &t) const;
  bool operator>(Time const &t) const;
  bool operator<(Time const &t) const;
  bool operator>=(Time const &t) const;
  bool operator<=(Time const &t) const;

private:
  int hour{}, minute{}, second{};
  void format_into_ostream(int const n, std::ostream &os) const;
};
// förstår inte riktigt varför man inte får använda friend (skulle då kunna lägga in klassen) Antar att det är dålig praxis då man inte vill att sådant i public ska komma åt sådant i private?
std::ostream &operator<<(std::ostream &os, const Time &t);
std::istream &operator>>(std::istream &is, Time &t);