#include "ghost.h"
#include "SFML/Graphics.hpp" //för colour

sf::Color stringToColor(const std::string &color)
{
  if (color == "red")
    return sf::Color::Red;
  // lägg till fler sen
  return sf::Color::White; // Default
}

Ghost::Ghost(sf::Vector2f const &start_position, Grid &grid, int speed, sf::Color const &color)
    : Entity(start_position, grid, speed, color)
{
  // Ghost class constructor body
}

std::string Ghost::get_color() const
{
  return color;
}

void Ghost::set_position(Point const &position)
{
  this->position = position;
}

Point Ghost::get_position() const
{
  return position;
}

// Blinky implementation
Blinky::Blinky(sf::Vector2f const &start_position, Grid &grid)
    : Ghost(start_position, grid, 100 /* example speed */, stringToColor("red")) {}
{
}

Point Blinky::get_chase_point() const
{
  // Implement chase logic specific to Blinky
}

Point Blinky::get_scatter_point() const
{
  // Implement scatter logic specific to Blinky
}

bool Blinky::is_angry() const
{
  return angry;
}

void Blinky::set_angry(bool angry)
{
  this->angry = angry;
}

// Implementations for Pinky and Clyde follow a similar pattern
