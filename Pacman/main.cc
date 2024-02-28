#include "full_game/YOUR_CODE_HERE/ghost.h"
// #include "SFML/Graphics.hpp"
#include "given.h "
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
// för kompilering på windows använd:  g++ .\main.cc .\given.cc .\full_game\YOUR_CODE_HERE\ghost.cc -o .\bin\pacman -I"C:\Users\Melker Gustafsson\TDIU20\Pacman"
// på laptopen, byt ut Melker Gustafsson mot boren
// Lägg till det under ifall smfl
//-I"C:/SFML-2.6.1/include" -L"C:/SFML-2.6.1/lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
// förstår intr varför min launch.json och tasks.json + cpp.properties löser det åt mig men aja
// kom ihåg att skapa en bin (mkdir bin) då ej bin ligger i git
using namespace std;

/*
  Ledning och Tips:

  - Modifiera stukturen till en header-fil och en implementationsfil
  - Utöka 'run()' och 'draw_map()' med övrig funktionalitet.
  - Lägg alla spöken i en lämplig behållare som en datamedlem.
  - Bryt ut stora kodblock till egna funktioner.
  - Använd hjälpfunktioner för att undvika duplicering av kod.
  - Tänk på att varje funktion inte borde vara längre än 25 rader.
 */

class Ghost_Tester
{

public:
  map<string, Ghost *> ghosts;
  Ghost_Tester()
      : pacman{}
  {
    ghosts["blinky"] = new Blinky(Point{3, 3}, "red");
    // Blinky newBlinky = Blinky(Point{3, 3}, "red");
    Blinky *blinky = new Blinky(Point{4, 7}, "red");
  }

  void run()
  {
    while (true)
    {
      // Point current_target = blinky->get_position();
      // Point next_target;

      // // Call select_new_target with both current and next target
      // blinky->select_new_target(current_target, next_target);

      draw_map();
      cout << "> ";

      string line{};
      getline(cin, line);
      istringstream iss{line};

      string color;
      int x, y;
      string command{};
      iss >> command;

      if (command == "chase")
      {
        // blinky->chase();
      }
      // if (iss >> color >> x >> y) // Successfully parsed color and position
      // {
      //   Point position{x, y};
      //   string key = color + " " + to_string(x) + "," + to_string(y); // skapa unik key för varje ghost

      //   if (color == "red")
      //   {
      //     ghosts[key] = new Blinky(position, color);
      //   }
      // }
      if (command == "pos")
      {
        Point new_pos{};
        iss >> new_pos.x >> new_pos.y;
        pacman.set_position(new_pos);
      }
      else
      {
        string color = command;
        int x, y;
        iss >> x >> y;
        Point new_pos{x, y};
        string key = color + " " + to_string(x) + "," + to_string(y); // skapa unik key för varje ghost
        if (color == "red")
        {
          ghosts[key] = new Blinky(new_pos, color);
        }
      }
      if (command == "dir")
      {
      }
      else if (command == "quit")
      {
        for (auto &pair : ghosts)
        {
          delete pair.second; // Delete the dynamically allocated Ghost
        }
        ghosts.clear();
        break;
      }
    }
  }

private:
  /*
    En hjälpfunktion som avgör vilka två tecken som ska ritas ut för en given position på
    spelplanen.
   */
  string to_draw(Point const &curr_pos)
  {
    string to_draw{"  "};
    Point pacmanPosition = pacman.get_position(); // för ghost då den inte är bereoende av pacman :D
    // Draw Pacman
    if (pacman.get_position() == curr_pos)
    {
      to_draw[1] = '@';
    }

    Point blinkyPos = blinky->get_position();
    if (blinkyPos == curr_pos)
    {
      to_draw[0] = 'B';
    }
    // Draw Ghosts

    for (const auto &pair : ghosts)
    {
      auto ghost = pair.second;
      if (ghost->get_position() == curr_pos)
      {
        to_draw[0] = toupper(ghost->get_color()[0]);
      }
      else if (ghost->get_target_position() == curr_pos)
      {
        to_draw[0] = tolower(ghost->get_color()[0]);
      }
    }

    return to_draw;
  }

  // för polimorfism, går inte annars om ej pointer
  Blinky *blinky;
  // unique_ptr<Blinky> blinky = make_unique<Blinky>(Point{3, 3}, "red"); //lekte runt lite, men kommer inte lösa vårt problem
  // Grid grid; behövs ej längre

  /*
    En hjälpfunktion för att rita ut spelplanen för testprogrammet.

    Itererar över varje rad och column i kartan. Index för raderna är flippade för att placera
    y = 0 längst ned.

    Varje punkt i kartan ritas som två tecken eftersom ett tecken i terminalen är ca dubbelt så
    högt som det är brett.
  */
  void draw_map()
  {
    cout << "+" << setfill('-') << setw(WIDTH * 2) << "-"
         << "+\n";

    for (int y{HEIGHT - 1}; y >= 0; --y)
    {
      cout << "|";
      for (int x{}; x < WIDTH; ++x)
      {
        cout << to_draw(Point{x, y});
      }
      cout << "|\n";
    }

    cout << "+" << setfill('-') << setw(WIDTH * 2) << "-"
         << "+" << endl;
  }

  Pacman pacman;
};

int main()
{
  Ghost_Tester gt{};
  gt.run();
  return 0;
}