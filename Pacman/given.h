#pragma once

/*
  I denna fil finns ett utval av kod fr�n det dina kollegor skrivit till ert pacman-projekt. Det �r
  precis det som du beh�ver f�r att skriva din del av koden.

  Tips: Du f�r ut�ka denna fil med saker som du beh�ver f�r att ditt program ska kompilera. Det �r
  �ven okej att ut�ka Point med fler operatorer om det skulle beh�vas.
 */

#include <stdexcept>
#include <iostream>

/*
  Globala variabler f�r storlek p� spelplanen.

  Din kollega som skrev detta �r medveten om att globala variabler �r d�ligt och borde undvikas, men
  har inte haft tid att �tg�rda det. I den slutgiltiga versionen av koden borde dessa s�klart l�sas
  fr�n en fil med konfigurationsdata.
 */
extern int WIDTH;
extern int HEIGHT;

/*
  Ett aggregat som anv�nd f�r att representera punkter och riktninar p� spelplanen.
  Aggregatet har ocks� hj�lpsamma operatorer som kan underl�tta din implementation.

 */
struct Point
{
  int x;
  int y;
};
bool operator==(Point const &lhs, Point const &rhs);
std::istream &operator>>(std::istream &is, Point &rhs);

// lagt till då så jag gjort mina "ghosts" är att de förväntar sig en grid objekt
class Grid
{
public:
  Grid() = default;
  static int get_width() { return WIDTH; }
  static int get_height() { return HEIGHT; }
};
/*
  En klass f�r att representera spelarfiguren. Detta �r en nedskalad version j�mf�rt med det som
  kollegan skrev till spelet. Notera att din kod inte beh�ver �ndras om man skulle g� fr�n denna
  implementaion till den faktiska implementationen.
 */
class Pacman
{
public:
  Pacman();

  Point get_position() const;
  void set_position(Point const &p);

  Point get_direction() const;
  void set_direction(Point const &p);

private:
  Point pos{};
  Point dir{};
};
