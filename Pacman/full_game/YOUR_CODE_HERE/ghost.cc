#include "ghost.h"
// #include "Sfml/Graphics.hpp"
// #include "given.h" //för basic testfall
// stort sett gjort om varenda klass så de ej använder SMFL, min förståelse är att main och given inte använder SMFL och därför bör detta programmet ej heller göra det
// tog mig bara runt 15 timmar att förstå det :(, men har iallafall bra förståelse över SMFL nu :/
using namespace std;
// kollade spec-sheeten behövs ej, bara en get color behövs :DDDD
//  sf::Color Ghost::get_sfml_color(const std::string &colorName)
//  {
//    if (colorName == "red")
//      return sf::Color::Red;
//    else if (colorName == "pink")
//      return sf::Color::Magenta; // Assuming pink maps to sf::Color::Magenta
//    else if (colorName == "orange")
//      return sf::Color(255, 165, 0); // Custom color, as SFML does not have a predefined orange
//    else
//      return sf::Color::White; // Default color
//  }

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
Point Ghost::get_target_position() const
{
  return Point{lastTargetPosition.x, lastTargetPosition.y};
}
Point Ghost::get_position()
{
  return Point{position.x, position.y};
}

void Ghost::select_new_target(const Point &PacmanPosition, Point &current_position, Point &target_position)
{
}

// Blinky constructor
Blinky::Blinky(Point const &start_position, string const &color)
    : Ghost(start_position, "red")
{
  // Blinky-specific initialization
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
    return Point{6, 6}; // vet inte om detta är bra då inte kommer funka om annorlunda plan
                        //  men int grid_width = grid.rows[0].size(); int grid_height = grid.rows.size(); . där  rows är inaccessible och har ingen blekaste om jag får ändra grid filen :/
  }
}
void Blinky::select_new_target(const Point &pacmanPosition, Point &current_target, Point &next_target)
{
  next_target = get_scatter_point(pacmanPosition);

  current_target = this->get_position();

  lastTargetPosition = next_target;
}
Point Blinky::get_target_position() const
{
  // return Point{lastTargetPosition.x, lastTargetPosition.y};
  return lastTargetPosition;
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
Point Blinky::chase(const Point &pacmanPosition)
{
  return pacmanPosition;
  // return pacman.get_position();
}
string Blinky::get_color() const
{
  return "red";
}

// Clyde constructor
