#include "ghost.h"
// lite osäker  "Lägg en (1) implemenationsfil med kod för alla spöken i mappen YOUR_CODE_HERE." och "Dina spök-klasser
// ska ligga på sin egen.h och.cc - fil, lämpligt namngivna." motsäger ju varandra, hade varit snyggare att ha varsin då de blir väldigt mycket kod i en fil men o andra sidan så ärver alla klassar från ghost och overridar ghost så utav den
// anledningen så passar det ändå att ha allt i en fil
using namespace std;

Ghost::Ghost(Point const &start_position, const string &colorName)
    : position(start_position), colorName(colorName)
{
  // position = start_position;
}

void Ghost::set_position(const Point &new_position)
{
  position.x = new_position.x;
  position.y = new_position.y;
}

Point Ghost::get_position()
{
  return Point{position.x, position.y};
}

// Blinky constructor
Blinky::Blinky(Point const &start_position, string const &)
    : Ghost(start_position, "red")
{
}
Point Blinky::get_scatter_point() const
{
  if (angry)
  {
    // return pacman.get_position();
    return pacmanPosition;
  }
  else
  {
    return Point{18, 21};
  }
}

bool Blinky::is_angry() const
{
  return angry; // Return the angry state
}

// self explanatory
void Blinky::set_angry(bool state)
{
  angry = state;
}
/*
returnerar en "Point" som blinky ska jaga.
*/
// använder may_be_unused för att undvika varningar om att variabler ej används, används i pinky och vill därför ha kvar den i alla klasser
Point Blinky::get_chase_point()
{
  return pacmanPosition;
  // return pacman.get_position();
}
string Blinky::get_color() const
{
  return "red";
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Pinky constructor
Pinky::Pinky(Point const &start_position, string const &)
    : Ghost(start_position, "pink")
{
}
Point Pinky::get_scatter_point() const
{
  return Point{0, 21};
}

Point Pinky::get_chase_point()
{
  return Ghost::CalculateTargetAhead(pacmanPosition, pacmanDirection, 2);
}

string Pinky::get_color() const
{
  return "pink";
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clyde constructor
Clyde::Clyde(Point const &start_position, std::string const &)
    : Ghost(start_position, "orange")
{
}
Point Clyde::get_scatter_point() const
{
  return Point{0, 0};
}

Point Clyde::get_chase_point()
{
  int distance = abs(position.x - pacmanPosition.x) + abs(position.y - pacmanPosition.y);

  if (distance <= 2)
  {
    // Ifall Clyde är inom 2 units av Pacman, target  scatter position.

    return Point{0, 0};
  }
  else
  {
    // Otherwise, target Pacman's position.
    return pacmanPosition;
  }
}
string Clyde::get_color() const
{
  return "orange";
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// INKY
Inky::Inky(Point const &start_position, string const &)
    : Ghost(start_position, "blue")
{
}
// hade ghost pacman & som parameter hade jag kunna gjort det här snyggare
Point Inky::CalculateInkysTarget(const Point &pacmanPosition, const Point &pacmanDirection, const Point &blinkyPosition) const
{
  Point Ahead = Ghost::CalculateTargetAhead(pacmanPosition, pacmanDirection, 2);
  Point inkysTargetBegin = {(Ahead.x - blinkyPosition.x), (Ahead.y - blinkyPosition.y)};
  Point inkysTarget = {(inkysTargetBegin.x + Ahead.x), (inkysTargetBegin.y + Ahead.y)};
  return inkysTarget;
}
// Point Inky::get_position()
// {
//   return CalculateInkysTarget(pacmanPosition, pacmanDirection, blinkyPosition);
// }
string Inky::get_color() const
{
  return "blue";
}
Point Inky::get_scatter_point() const
{
  return CalculateInkysTarget(pacmanPosition, pacmanDirection, blinkyPosition);
}
Point Inky::get_chase_point()
{
  return CalculateInkysTarget(pacmanPosition, pacmanDirection, blinkyPosition);
}
