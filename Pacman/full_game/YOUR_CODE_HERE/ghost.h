#ifndef GHOST_H
#define GHOST_H

// #include "entity.h"
// hade tidigare så att ghost tidigare var en extension av entity class. men efter att ha kollat igenom main.cc och given.h känns det som att det är fel tillvägagångssätt.
#include <string>
#include "SFML/Graphics.hpp"
// #include "pacman.h" //för hela spelet
#include "given.h" //för basic testfall
class Ghost
{
public:
  Ghost(Pacman &pacman, sf::Vector2f const &start_position, Grid &grid, int speed, std::string const &color, Point const &scatter_position);
  virtual ~Ghost() = default;

  virtual Point get_scatter_point() const = 0;
  virtual Point chase() = 0;
  virtual void select_new_target(sf::Vector2f &current_position, sf::Vector2i &target_position) const = 0;
  void set_position(const Point &new_position);
  Point get_position() const;
  virtual std::string get_color() const = 0;

protected:
  Pacman &pacman;
  Point scatter_position;
  Grid &grid;                  // Reference to a Grid object
  int speed;                   // Speed of the ghost
  sf::Vector2f start_position; // Added based on constructor usage
  sf::Vector2f position;
  std::string colorName;
};

class Blinky : public Ghost
{
public:
  Blinky(Pacman &pacman, sf::Vector2f const &start_position, Grid &grid, int speed, std::string const &color, Point const &scatter_position);
  Point get_scatter_point() const override;
  void select_new_target(sf::Vector2f &current_target, sf::Vector2i &next_target) const override;
  bool is_angry() const;
  void set_angry(bool state);
  Point chase() override;
  std::string get_color() const override;

private:
  bool angry = false;
};
#endif
