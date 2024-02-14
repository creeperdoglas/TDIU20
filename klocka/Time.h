#pragma once // endast kompileras en gång
#include <iostream>
#include <string>

// Information om komplettering:
//   Siffrorna hänvisar till rättningsprotokollet som finns på
//   kurshemsidan -> läsning -> Literatur -> "Uppgruppens bedömningsprotokoll"
//   Kompletteringen kan gälla hela filen och alla filer i labben,
//   så får ni komplettering på en sak, kan samma sak förekomma på
//   fler ställen utan att jag skrivit det.
//
//   Komplettering lämnas in via sendlab efter senast en (1) vecka
//
//   Har ni frågor om kompletteringen kan ni maila mig på:
//   Malte.Nilsson@liu.se

// Komplettering: Interna medlemsfunktioner i den publika delen.
// KLART, check for invalid input låg fel

// Kommentar: pragma once ingår inte i kursen och är kompilator "specefikt"

// Komplettering (bonus): operator+ för kommutativa fallet saknas.
// KLART

// Saknar operatorer för Bonus
// += och -=
// KLART

class Time
{
public:
  Time() = default;
  Time(int const h, int const m, int const s);
  Time(std::string const &t);

  int get_hour() const;
  int get_minute() const;
  int get_second() const;

  bool is_am() const;
  std::string to_string(const bool = false) const; // till att byta mellan 24 och 12 timmars
  // operator std::string() const;                    // konvertera Time till sträng

  Time operator+(int const n) const; // Lägger till N sekunder
  Time operator++(int);              // post increment
  Time &operator++();
  Time &operator+=(int const n);

  Time operator-(int const n) const; // tar bort sekunder
  Time operator--(int);              // post decrement
  Time &operator--();
  Time &operator-=(int const n);

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
  bool check_for_invalid_input(int const h, int const m, int const s);
};
// förstår inte riktigt varför man inte får använda friend (skulle då kunna lägga in klassen) Antar att det är dålig praxis då man inte vill att sådant i public ska komma åt sådant i private?
//// Det stämmer
std::ostream &operator<<(std::ostream &os, const Time &t);
std::istream &operator>>(std::istream &is, Time &t);
Time operator+(int n, const Time &t); // för kommuntativa fallet