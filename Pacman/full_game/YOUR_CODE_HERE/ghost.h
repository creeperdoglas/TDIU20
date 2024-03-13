#ifndef GHOST_H
#define GHOST_H

// hade tidigare så att ghost tidigare var en extension av entity class. men efter att ha kollat igenom main.cc och given.h känns det som att det är fel tillvägagångssätt.
#include <string>
#include "given.h" //för basic testfall
class Ghost
{
public:
  Ghost(Point const &start_position, std::string const &color);
  virtual ~Ghost() = default;
  virtual Point get_scatter_point() const = 0;
  virtual Point get_chase_point() = 0;
  void set_position(const Point &new_position);
  Point get_position();
  virtual std::string get_color() const = 0;

  static Point CalculateTargetAhead(const Point &pacmanPosition, const Point &pacmanDirection, int stepsAhead)
  {
    return Point{
        pacmanPosition.x + pacmanDirection.x * stepsAhead,
        pacmanPosition.y + pacmanDirection.y * stepsAhead};
  }
  void update(const Point &pacmanPosition, const Point &pacmanDirection)
  {
    this->pacmanPosition = pacmanPosition;
    this->pacmanDirection = pacmanDirection;
  }

protected:
  Point position;
  Point pacmanPosition;
  Point pacmanDirection;
  std::string colorName;
};

class Blinky : public Ghost
{
public:
  Blinky(Point const &start_position, std::string const &color);
  Point get_scatter_point() const override;

  bool is_angry() const;
  void set_angry(bool state);
  Point get_chase_point() override;
  std::string get_color() const override;

private:
  bool angry = false;
};

class Pinky : public Ghost
{
public:
  Pinky(Point const &start_position, std::string const &color);
  Point get_scatter_point() const override;

  Point get_chase_point() override;
  std::string get_color() const override;
};

class Clyde : public Ghost
{
public:
  Clyde(Point const &start_position, std::string const &color);
  Point get_scatter_point() const override;
  Point get_chase_point() override;
  std::string get_color() const override;
};
class Inky : public Ghost
{
public:
  Inky(Point const &start_position, std::string const &color);
  Point CalculateInkysTarget(const Point &pacmanPosition, const Point &pacmanDirection, const Point &blinkyPosition) const;
  // Point get_position() override;
  std::string get_color() const override;
  Point get_scatter_point() const override;
  Point get_chase_point() override;

  // void set_pacman_position(const Point &new_position)
  // {
  //   pacmanPosition = new_position;
  // }

  // void set_pacman_direction(const Point &new_direction)
  // {
  //   pacmanDirection = new_direction;
  // }

  void set_blinky_position(const Point &new_position)
  {
    blinkyPosition = new_position;
  }

private:
  // Point pacmanPosition;
  // Point pacmanDirection;
  Point blinkyPosition;
};
#endif
