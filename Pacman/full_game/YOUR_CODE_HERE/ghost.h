#ifndef GHOST_H
#define GHOST_H

#include "entity.h"
#include "pacman.h"
#include <string>

class Ghost : public Entity
{
public:
  Ghost(Pacman &pacman, sf::Vector2f const &start_position, Grid &grid, int speed, std::string const &color, Point const &scatter_position);
  virtual ~Ghost() = default;

  virtual Point get_scatter_point() const = 0; // virtual behövs för att kunna override en base class funktion, detta gör så att blinky exempelvis kan ha en egen scatter_point och de andra en annan. korrekt?
  virtual void chase() = 0;

protected:
  Pacman &pacman;
  Point scatter_position;
};
// Specifika ghost-klasser
class Blinky : public Ghost
{
public:
  Blinky(Pacman &pacman, sf::Vector2f const &start_position, Grid &grid, int speed, std::string const &color, Point const &scatter_position);
  Point get_scatter_point() const override;
  bool is_angry() const { return angry; }
  void set_angry(bool state) { angry = state; }
  void chase() override;

private:
  bool angry = false;
};

#endif // GHOST_H
