#include "ghost.h"
// lite osäker  "Lägg en (1) implemenationsfil med kod för alla spöken i mappen YOUR_CODE_HERE." och "Dina spök-klasser
// ska ligga på sin egen.h och.cc - fil, lämpligt namngivna." motsäger ju varandra, hade varit snyggare att ha varsin då de blir väldigt mycket kod i en fil men o andra sidan så ärver alla klassar från ghost och overridar ghost så utav den
// anledningen så passar det ändå att ha allt i en fil
using namespace std;

Ghost::Ghost(Point const &start_position, const string &colorName)
    : position(start_position), colorName(colorName), blinkyPosition(start_position), pinkyPosition(start_position)
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
Point Blinky::get_scatter_point(const Point &pacmanPosition) const
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
void Blinky::set_position(const Point &new_position)
{
  Ghost::set_position(new_position); // snyggare lösning
}
Point Blinky::get_position()
{
  return Point{position.x, position.y};
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
Point Blinky::get_chase_point(const Point &pacmanPosition, [[maybe_unused]] const Point &pacmanDirection)
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
Point Pinky::get_scatter_point([[maybe_unused]] const Point &pacmanPosition) const
{
  return Point{0, 21};
}

void Pinky::set_position(const Point &new_position)
{
  Ghost::set_position(new_position);
}
Point Pinky::get_position()
{
  return Point{position.x, position.y};
}
Point Pinky::get_chase_point(const Point &pacmanPosition, const Point &pacmanDirection)
{
  Point target = pacmanPosition;
  if (pacmanDirection.x == 1 && pacmanDirection.y == 0)
  {                            // hade först detta för att wrapa men enligt labb assisten behövdes det ej
    target.x = (target.x + 2); //% WIDTH; // Move right and wrap around horizontally
  }
  else if (pacmanDirection.x == -1 && pacmanDirection.y == 0)
  {
    target.x = (target.x - 2); // % WIDTH; // Move left and wrap around horizontally
  }
  else if (pacmanDirection.x == 0 && pacmanDirection.y == 1)
  {
    target.y = (target.y + 2); //% HEIGHT; // Move up and wrap around vertically
  }
  else if (pacmanDirection.x == 0 && pacmanDirection.y == -1)
  {
    target.y = (target.y - 2); // Move down and wrap around vertically
  }
  return target;
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
Point Clyde::get_scatter_point([[maybe_unused]] const Point &pacmanPosition) const
{
  return Point{0, 0};
}

void Clyde::set_position(const Point &new_position)
{
  Ghost::set_position(new_position);
}
Point Clyde::get_position()
{
  return Point{position.x, position.y};
}
Point Clyde::get_chase_point(const Point &pacmanPosition, [[maybe_unused]] const Point &pacmanDirection)
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
Point Inky::CalculateTarget(const Point &pinkyPosition, const Point &blinkyPosition) const
{
  // Point twoStepsAhead = {((pacmanPosition.x + 2) * target.x), ((pacmanPosition.y + 2) * target.y)};

  // // Calculate the vector from Blinky to the point two steps ahead of Pacman
  // Point vectorToTwoStepsAhead = {(twoStepsAhead.x - blinkyPosition.x), (twoStepsAhead.y - blinkyPosition.y)};

  // // Calculate Inky's target by extending the line the same distance beyond the two steps ahead of Pacman
  // Point inkysTarget = {(twoStepsAhead.x + vectorToTwoStepsAhead.x), (twoStepsAhead.y + vectorToTwoStepsAhead.y)};
  Point inkysTargetBegin = {(pinkyPosition.x - blinkyPosition.x), (pinkyPosition.y - blinkyPosition.y)};
  Point inkysTarget = {(inkysTargetBegin.x + pinkyPosition.x), (inkysTargetBegin.y + pinkyPosition.y)};
  return inkysTarget;
}
Point Inky::get_position()
{
  return CalculateTarget(pinkyPosition, blinkyPosition);
}
string Inky::get_color() const
{
  return "blue";
}
Point Inky::get_scatter_point([[maybe_unused]] const Point &pacmanPosition) const
{
  return CalculateTarget(pinkyPosition, blinkyPosition);
}
Point Inky::get_chase_point([[maybe_unused]] const Point &pacmanPosition, [[maybe_unused]] const Point &pacmanDirection)
{
  return CalculateTarget(pinkyPosition, blinkyPosition);
}
void Inky::set_blinky_position(const Point &new_position)
{
  Ghost::blinkyPosition = new_position;
}
void Inky::set_pinky_position(const Point &new_position)
{
  Ghost::pinkyPosition = new_position;
}
