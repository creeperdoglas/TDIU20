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

Ghost::Ghost(Pacman &pacman, Point const &start_position, Grid &grid, int speed, const std::string &colorName, Point const &scatter_position)
    : pacman(pacman), start_position(start_position), grid(grid), speed(speed), colorName(colorName), scatter_position(scatter_position)
{
  // constructor implementation
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

// Blinky constructor
Blinky::Blinky(Pacman &pacman, Point const &start_position, Grid &grid, int speed, std::string const &color, Point const &scatter_position)
    : Ghost(pacman, start_position, grid, 100, "red", scatter_position)
{
  // Blinky-specific initialization
}
Point Blinky::get_scatter_point() const
{
  if (angry)
  {
    return pacman.get_position();
  }
  else
  {
    return Point{6, 6}; // vet inte om detta är bra då inte kommer funka om annorlunda plan
                        //  men int grid_width = grid.rows[0].size(); int grid_height = grid.rows.size(); . där  rows är inaccessible och har ingen blekaste om jag får ändra grid filen :/
  }
}
void Blinky::select_new_target(Point &current_target, Point &next_target)
{
  if (angry)
  {
    // Direct chase: Target is Pacman's current position
    Point pacmanPosition = pacman.get_position();
    next_target = Point{pacmanPosition.x, pacmanPosition.y};
  }
  else
  {
    // Scatter mode: Target is a fixed point, e.g., (6, 6)
    next_target = Point{6, 6};
  }
  lastTargetPosition = next_target;
}
Point Blinky::get_target_position() const
{
  return Point{lastTargetPosition.x, lastTargetPosition.y};
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
Point Blinky::chase()
{
  return pacman.get_position();
}
string Blinky::get_color() const
{
  return "red";
}

// Clyde constructor
