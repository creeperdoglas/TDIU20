#pragma once
#include <fstream>
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

private:
  int hour{}, minute{}, second{};
  bool check_for_invalid_input(int const h, int const m, int const s) const;
};