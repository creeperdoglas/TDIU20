#include "ghost.h"
#include "entity.h"          //kanske ta bort, låter vara kvar så länge, gör ändå ingen skillnad pga pragma once
#include "SFML/Graphics.hpp" //för color
using namespace std;

sf::Color get_color(const string &color)
{
  if (color == "red")
    return sf::Color::Red;
  else if (color == "pink")
    return sf::Color::Magenta;
  else if (color == "orange")
    return sf::Color(255, 165, 0); // Orange , fanns ej orange i sfml. Hoppas detta funkar
  return sf::Color::White;         // Default
}

Ghost::Ghost(Pacman &pacman, sf::Vector2f const &start_position, Grid &grid, int speed, std::string const &color, Point const &scatter_position)
    : Entity(start_position, grid, speed, get_color(color)), // borde nu korrekt konvertera string till sf::Color
      pacman(pacman),
      scatter_position(scatter_position)
{
  // Constructor body
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
