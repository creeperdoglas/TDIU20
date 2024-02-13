#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept> //för throw invalid_argument
#include <iomanip>   // för std::setw and std::setfill
#include <sstream>
#include "Time.h"

// Information om komplettering:
//   Kompletteringen kan gälla hela filen och alla filer i labben,
//   så får ni komplettering på en sak, kan samma sak förekomma på
//   fler ställen utan att jag skrivit det.
//
//   Komplettering lämnas in via sendlab efter senast en (1) vecka
//
//   Har ni frågor om kompletteringen kan ni maila mig på:
//   Malte.Nilsson@liu.se

// Komplettering: Upprepa inte strömmanipulatorer som gäller tills vidare.
// KLART

// Komplettering: stoi kastar ett eget undantag som inte ska läcka vidare till er användare.
// KLART

// Komplettering: Kodupprepning i stegningsoperatorerna.
// KLART

// Komplettering: operator string används inte och testas inte.
// tog bort, KLART? kom fram till att det inte behövdes då jag redan har en to_string som gör allt jag behöver.

// Komplettering: En testfil ska pröva de funktioner som
//   ni har skapat. Det innebär att man vill pröva alla
//   möjliga fall (även specialfall). Vi vill ju vara säkra
//   på att vi har en funktion som fungerar. En bra fråga är:
//   "Övertygar detta den som rättar att er funktion
//   fungerar utan att kolla i Time.cc-filen?"

// Kommentar: skriv datamedlemsinitieringslistan på egen rad
// Kommentar/Tips: Om det enda som returneras i en if-sats
// är true och else false kan man returnera villkoret direkt.
// Ex:
// if (x == 10)
//     return true;
// else
//     return false;
//
// Kan skrivas som endast:
// return x == 10;

// Komplettering (bonus) operator- fungerar inte korrekt
// funkar inte för t.ex
// 	Time t{0, 0, 0};
//	t = t - 129605;
// KLART

using namespace std;

Time::Time(int const h, int const m, int const s) : hour{h}, minute{m}, second{s}
{
  if (check_for_invalid_input(h, m, s))
  {
    throw invalid_argument{"invalid_input"}; // std:: innan?
  }
}
bool Time::check_for_invalid_input(int const h, int const m, int const s)
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

// skapa en Time instans från sträng till format HH:MM:SS
Time::Time(string const &t) // const &t?
{
  if (t.size() == 8 && t[2] == ':' && t[5] == ':')
  {
    try
    {

      hour = stoi(t.substr(0, 2));   // börja på pos 0 och ta två chars, gör sedan om till int
      minute = stoi(t.substr(3, 2)); // samma här
      second = stoi(t.substr(6, 2)); // och här
    }
    catch (const invalid_argument &)
    {
      throw invalid_argument{"invalid_input"};
    }
    catch (const out_of_range &)
    {
      throw invalid_argument{"invalid_input"};
    }
    if (check_for_invalid_input(hour, minute, second))
    {
      throw invalid_argument{"invalid_input"};
    }
  }
  else
  {
    throw invalid_argument{"invalid_format"}; // borde behövas då den innan endast kollar om exempelvis timmar är under 24?
  }
}

bool Time::is_am() const
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

string Time::to_string(const bool am_pm_format) const
{
  ostringstream ss{};

  int display_hour = hour;
  if (am_pm_format)
  {
    if (hour == 0)
    {
      display_hour = 12; // 12 AM
    }
    else if (hour > 12)
    {
      display_hour = hour - 12; // konvertera till 12-timmars format
    }
  }

  ss << setw(2) << setfill('0') << display_hour;
  ss << ':' << setw(2) << minute;
  ss << ':' << setw(2) << second;

  if (am_pm_format)
  {
    ss << (is_am() ? " AM" : " PM");
  }

  return ss.str();
}
// gör så att om n < 10 lägg till 0a.
void Time::format_into_ostream(int const n, ostream &os) const
{
  if (n < 10)
  {
    os << 0;
  }
  os << n;
}

// gammal operator+ , kom fram till att den tar överdrivet lång tid vid stora tal. Den nya använder inte en loop och borde (är) snabbare :D
//  Time Time::operator+(int const n) const
//  {
//    Time temp{hour, minute, second};
//    if (n < 0)
//    {
//      temp = temp - (-n);
//    }
//    else
//    {

//      for (int i{}; i < n; i++)
//      {
//        temp++;
//    }
//   }
//   return temp;
// }

Time Time::operator+(int const n) const
{
  // Konvertera tid till totala sekunder
  int total_seconds = hour * 3600 + minute * 60 + second;

  // Lägg till n sekunder
  total_seconds += n;

  // för överflöd
  total_seconds = (total_seconds + 24 * 3600) % (24 * 3600);

  // Konvertera tillbaka till timmar, minuter och sekunder
  int new_hour = total_seconds / 3600;
  // total_seconds %= 3600; // för att ++ ska fungera
  int new_minute = (total_seconds % 3600) / 60;
  int new_second = total_seconds % 60;

  // Skapa och returnera
  return Time(new_hour, new_minute, new_second);
}
Time Time::operator++(int)
{
  // skapar en kopia och returnerar
  Time t{*this};
  ++(*this); // lade till prefix i h fil, nu funkar det.
  return t;
}
Time &Time::operator++()
{
  *this = *this + 1;
  return *this;
}
Time &Time::operator+=(int const n)
{
  *this = *this + n;
  return *this;
}

Time Time::operator-(int const n) const
{
  // konvertera
  int total_seconds = hour * 3600 + minute * 60 + second;

  // subtrahera
  total_seconds -= n;

  // för överflöd
  if (total_seconds < 0)
  {
    total_seconds = (total_seconds % (24 * 3600) + (24 * 3600)) % (24 * 3600); //"wrap around" till förra dagen
  }

  // Konvertera tillbaka till timmar, minuter och sekunder
  int new_hour = total_seconds / 3600;
  total_seconds %= 3600; // behövs :/
  int new_minute = total_seconds / 60;
  int new_second = total_seconds % 60;

  // Skapa och returnera
  return Time(new_hour, new_minute, new_second);
}
Time Time::operator--(int)
{
  Time t{*this};
  --(*this);
  return t;
}
Time &Time::operator--()
{
  *this = *this - 1;
  return *this;
}
Time &Time::operator-=(int const n)
{
  *this = *this - n;
  return *this;
}
bool Time::operator==(Time const &t) const
{
  if (hour == t.hour && minute == t.minute && second == t.second)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Time::operator!=(Time const &t) const
{
  return !(*this == t);
}

bool Time::operator<(Time const &t) const
{
  if (hour < t.hour)
  {
    return true;
  }
  else
  {
    if (hour == t.hour && minute < t.minute)
    {
      return true;
    }
    else
    {
      if (hour == t.hour && minute == t.minute && second < t.second)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  }
}

bool Time::operator>(Time const &t) const
{
  return (t < *this);
}

bool Time::operator<=(Time const &t) const
{
  if (*this < t || *this == t)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Time::operator>=(Time const &t) const
{
  if (*this > t || *this == t)
  {
    return true;
  }
  else
  {
    return false;
  }
}

// Time::operator string() const
// {
//   return to_string();
// }

int Time::get_hour() const
{
  return hour;
}

int Time::get_minute() const
{
  return minute;
}

int Time::get_second() const
{
  return second;
}

ostream &operator<<(ostream &os, Time const &t)
{
  os << t.to_string();
  return os;
}

istream &operator>>(istream &is, Time &t)
{
  int h, m, s;
  char c1, c2;
  is >> h >> c1 >> m >> c2 >> s;

  // Skapa ett nytt objekt för validering och tilldelning, försökte använda en if sats förut med check_for_invalid input, funkade ej (antar då private?), så gjorde om såhär
  try
  {
    Time temp(h, m, s); // Konstruktören kommer att kasta ett undantag om indata är ogiltig
    t = temp;           // Uppdatera t om inga undantag kastas
  }
  catch (const std::invalid_argument &)
  {
    is.setstate(ios::failbit); // Ange felstatus vid ogiltig inmatning
  }

  return is;
}
