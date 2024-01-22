#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "Time.h"

using namespace std;
Time::Time(int const h, int const m, int const s) : hour{h}, minute{m}, second{s}
{
  if (check_for_invalid_input(h, m, s))
  {
    throw invalid_argument{"invalid_input"}; // std:: innan?
  }
}

// skapa en Time instans från sträng till format HH:MM:SS
Time::Time(string const &t)
{
  if (t.size() == 8 && t[2] == ":" && t[5] == ":") // ta bort en const, gör senare, vill se om det kanske kan funka ändå
  {
    hour = stoi(t.substr(0, 2));   // börja på pos 0 och ta två chars, gör sedan om till int
    minute = stoi(t.substr(3, 2)); // samma här
    second = stoi(t.substr(6, 2)); // och här
  }
  else if (check_for_invalid_input(hour, minute, second))
  {
    throw invalid_argument{"invalid_input"}; // std:: innan?
  }
  else
  {
    throw invalid_argument{"invalid_format"}; // borde behövas då den innan endast kollar om exempelvis timmar är under 24?
  }
}

bool check_for_invalid_input(int const h, int const m, int const s)
{
  if (h > 23 || h < 0 || m > 59 || m < 0 || s > 59 || s < 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Time::is_am()
{
  if (hour < 12)
  {
    return true;
  }
  else
  {
    return false;
  }
}
