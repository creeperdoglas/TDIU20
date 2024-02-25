#include "ghost.h"
#include "Sfml/Graphics.hpp"
// #include "given.h" //för basic testfall
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

Ghost::Ghost(Pacman &pacman, sf::Vector2f const &start_position, Grid &grid, int speed, const std::string &colorName, Point const &scatter_position)
    : pacman(pacman), start_position(start_position), grid(grid), speed(speed), colorName(colorName), scatter_position(scatter_position)
{
  // Your constructor implementation
}

void Ghost::set_position(const Point &new_position)
{
  position.x = static_cast<float>(new_position.x);
  position.y = static_cast<float>(new_position.y);
}

Point Ghost::get_position() const
{
  return Point{static_cast<int>(position.x), static_cast<int>(position.y)};
}

// Blinky constructor
Blinky::Blinky(Pacman &pacman, sf::Vector2f const &start_position, Grid &grid, int speed, std::string const &color, Point const &scatter_position)
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
void Blinky::select_new_target(sf::Vector2f &current_target, sf::Vector2i &next_target) const
{
  if (angry)
  {
    // Direct chase: Target is Pacman's current position
    Point pacmanPosition = pacman.get_position();
    next_target = sf::Vector2i(pacmanPosition.x, pacmanPosition.y);
  }
  else
  {
    // Scatter mode: Target is a fixed point, e.g., (6, 6)
    next_target = sf::Vector2i(6, 6);
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
Point Blinky::chase()
{
  return pacman.get_position();
}
string Blinky::get_color() const
{
  return "red";
}

// Clyde constructor
