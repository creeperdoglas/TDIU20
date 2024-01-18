#pragma once // endast kompileras en gång
#include <iostream>
#include <sstream>
#include <vector>
class Time
{
public:
  Time() = default;
  Time(int const h, int const m, int const s);
  Time(std::string const &t);

  int get_hour() const;
  int get_minute() const;
  int get_second() const;

  bool is_am();
  std::string to_string(const bool = false) const; // till att byta mellan 24 och 12 timmars
  operator std::string() const;                    // konvertera Time till sträng

  Time operator+(int const n) const; // Lägger till N sekunder
  Time operator++(int);              // post increment

  Time operator-(int const n) const; // tar bort sekunder
  Time operator--(int);              // post decrement

  // jämförelser
  bool operator==(Time const &t) const;
  bool operator!=(Time const &t) const;
  bool operator>(Time const &t) const;
  bool operator<(Time const &t) const;
  bool operator>=(Time const &t) const;
  bool operator<=(Time const &t) const;

private:
  int hour{}, minute{}, second{};
  bool check_for_invalid_input(int const h, int const m, int const s);
};