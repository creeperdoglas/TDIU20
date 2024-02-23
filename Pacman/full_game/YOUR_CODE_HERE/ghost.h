#ifndef GHOST_H
#define GHOST_H

#include "entity.h"
#include <string>

class Ghost : public Entity
{
public:
  Ghost(Point const &start_position, Grid &grid, std::string const &color);
  virtual ~Ghost() = default;

  // Virtual functions for behavior specific to each ghost
  virtual Point get_chase_point() const = 0;
  virtual Point get_scatter_point() const = 0;
  virtual std::string get_color() const;

  // common functions för alla spöken
  void set_position(Point const &position);
  Point get_position() const;

protected:
  std::string color;
  Point position;
};

// Specifika ghost-klasser
class Blinky : public Ghost
{
public:
  Blinky(Point const &start_position, Grid &grid);
  Point get_chase_point() const override;
  Point get_scatter_point() const override;
  bool is_angry() const;
  void set_angry(bool angry);

private:
  bool angry;
};

class Pinky : public Ghost
{
public:
  Pinky(Point const &start_position, Grid &grid);
  Point get_chase_point() const override;
  Point get_scatter_point() const override;
};

class Clyde : public Ghost
{
public:
  Clyde(Point const &start_position, Grid &grid);
  Point get_chase_point() const override;
  Point get_scatter_point() const override;
};

#endif // GHOST_H
