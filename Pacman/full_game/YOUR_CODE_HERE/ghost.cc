#include "ghost.h"
// lite osäker  "Lägg en (1) implemenationsfil med kod för alla spöken i mappen YOUR_CODE_HERE." och "Dina spök-klasser
// ska ligga på sin egen.h och.cc - fil, lämpligt namngivna." motsäger ju varandra, hade varit snyggare att ha varsin då de blir väldigt mycket kod i en fil men o andra sidan så ärver alla klassar från ghost och overridar ghost så utav den
// anledningen så passar det ändå att ha allt i en fil
//  stort sett gjort om varenda klass så de ej använder SMFL, min förståelse är att main och given inte använder SMFL och därför bör detta programmet ej heller göra det
//  tog mig bara runt 15 timmar att förstå det :(, men har iallafall bra ("bra") förståelse över SMFL nu :/
using namespace std;
// kollade spec-sheeten behövs ej, bara en get color behövs :DDDD

// Ghost::Ghost(Pacman &pacman, Point const &start_position, Grid &grid, int speed, const std::string &colorName, Point const &scatter_position)
//     : pacman(pacman), start_position(start_position), grid(grid), speed(speed), colorName(colorName), scatter_position(scatter_position)
// anledning till att gör om är att grid, speed och scatter position ej används. pacman användes men kan istället kallas med en return och gör så att min ghost inte är beroende av pacman, speciellt eftersom allt det ska göra är att hämta pacman position
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
// Point Ghost::get_target_position() const
// {
//   return Point{lastTargetPosition.x, lastTargetPosition.y};
// }
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
  // position.x = new_position.x;
  // position.y = new_position.y;
  Ghost::set_position(new_position); // snyggare lösning
}
// Point Blinky::get_target_position() const
// {
//   // return Point{lastTargetPosition.x, lastTargetPosition.y};
//   return lastTargetPosition;
// }
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
[[maybe_unused]] Point Blinky::get_chase_point(const Point &pacmanPosition, [[maybe_unused]] const Point &pacmanDirection)
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
// Point Pinky::get_target_position() const
// {
//   return lastTargetPosition;
// }
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
// Point Clyde::get_target_position() const
// {
//   return lastTargetPosition;
// }
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
Point Inky::CalculateTarget(const Point &PinkyPosition, const Point &blinkyPosition) const
{
  // Point target = pacmanPosition;
  // if (pacmanDirection.x == 1 && pacmanDirection.y == 0)
  // {                            // hade först detta för att wrapa men enligt labb assisten behövdes det ej
  //   target.x = (target.x + 2); //% WIDTH; // Move right and wrap around horizontally
  // }
  // else if (pacmanDirection.x == -1 && pacmanDirection.y == 0)
  // {
  //   target.x = (target.x - 2); // % WIDTH; // Move left and wrap around horizontally
  // }
  // else if (pacmanDirection.x == 0 && pacmanDirection.y == 1)
  // {
  //   target.y = (target.y + 2); //% HEIGHT; // Move up and wrap around vertically
  // }
  // else if (pacmanDirection.x == 0 && pacmanDirection.y == -1)
  // {
  //   target.y = (target.y - 2); // Move down and wrap around vertically
  // }

  // Point twoStepsAhead = {((pacmanPosition.x + 2) * target.x), ((pacmanPosition.y + 2) * target.y)};

  // // Calculate the vector from Blinky to the point two steps ahead of Pacman
  // Point vectorToTwoStepsAhead = {(twoStepsAhead.x - blinkyPosition.x), (twoStepsAhead.y - blinkyPosition.y)};

  // // Calculate Inky's target by extending the line the same distance beyond the two steps ahead of Pacman
  // Point inkysTarget = {(twoStepsAhead.x + vectorToTwoStepsAhead.x), (twoStepsAhead.y + vectorToTwoStepsAhead.y)};
  Point inkysTargetBegin = {(PinkyPosition.x - blinkyPosition.x), (PinkyPosition.y - blinkyPosition.y)};
  Point inkysTarget = {(inkysTargetBegin.x + PinkyPosition.x), (inkysTargetBegin.y + PinkyPosition.y)};
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
// Point Inky::get_target_position() const
// {
//   return CalculateTarget(pacmanPosition, pacmanDirection, blinkyPosition);
// }
Point Inky::get_scatter_point([[maybe_unused]] const Point &pacmanPosition) const
{
  Point tihi = CalculateTarget(pinkyPosition, blinkyPosition);
  return tihi;
}
Point Inky::get_chase_point([[maybe_unused]] const Point &pacmanPosition, [[maybe_unused]] const Point &pacmanDirection)
{
  Point tihi = CalculateTarget(pinkyPosition, blinkyPosition);
  // cout << "Inky's position: " << tihi.x << ", " << tihi.y << endl;
  return tihi;
}
