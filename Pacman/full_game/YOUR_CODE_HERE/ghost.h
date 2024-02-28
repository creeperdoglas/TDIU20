#ifndef GHOST_H
#define GHOST_H

// #include "entity.h"
// hade tidigare så att ghost tidigare var en extension av entity class. men efter att ha kollat igenom main.cc och given.h känns det som att det är fel tillvägagångssätt.
#include <string>
// #include "SFML/Graphics.hpp"
// #include "pacman.h" //för hela spelet
#include "given.h" //för basic testfall
class Ghost
{
public:
  Ghost(Point const &start_position, std::string const &color);
  virtual ~Ghost() = default;
  virtual Point get_scatter_point(const Point &pacmanPosition) const = 0;
  virtual Point chase(const Point &pacmanPosition) = 0;
  virtual void select_new_target(const Point &pacmanPosition, Point &current_position, Point &target_position) = 0;
  void set_position(const Point &new_position);
  virtual Point get_position();
  virtual std::string get_color() const = 0;
  virtual Point get_target_position() const = 0;

protected:
  // kom ihåg att ta en titt innan jag lämnar in sen, har lagt till och tagit bort massvis av funktioner, någon lär inte användas
  // Pacman &pacman;
  // Point scatter_position;
  // Grid &grid;           // Reference to a Grid object
  // int speed;            // Speed of the ghost
  Point start_position; // Added based on constructor usage
  Point position;
  std::string colorName;
  Point lastTargetPosition;
};

class Blinky : public Ghost
{
public:
  Blinky(Point const &start_position, std::string const &color);
  Point get_scatter_point(const Point &pacmanPosition) const override;
  void select_new_target(const Point &pacmanPosition, Point &current_target, Point &next_target) override;
  bool is_angry() const;
  void set_angry(bool state);
  Point chase(const Point &pacmanPosition) override;
  std::string get_color() const override;
  Point get_target_position() const override;
  Point get_position() override;

private:
  bool angry = false;
};
#endif
