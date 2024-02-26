#include "full_game/YOUR_CODE_HERE/ghost.h"
// #include "SFML/Graphics.hpp"
#include "given.h "
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
// för kompilering på windows använd:  g++ .\main.cc .\given.cc .\full_game\YOUR_CODE_HERE\ghost.cc -o .\bin\pacman -I"C:\Users\Melker Gustafsson\TDIU20\Pacman" -I"C:/SFML-2.6.1/include" -L"C:/SFML-2.6.1/lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
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
  std::map<string, Ghost *> ghosts;
  Ghost_Tester()
      : pacman{}
  {
    ghosts["blinky"] = new Blinky(pacman, Point{3, 3}, grid, 100, "red", Point{6, 6});
  }

  void run()
  {
    while (true)
    {
      draw_map();
      cout << "> ";

      string line{};
      getline(cin, line);
      istringstream iss{line};

      string command{};
      iss >> command;
      if (command == "chase")
      {
        blinky->chase();
      }
      if (command == "pos")
      {
        Point new_pos{};
        iss >> new_pos.x >> new_pos.y;
        pacman.set_position(new_pos);
      }
      else if (command == "dir")
      {
      }
      else if (command == "quit")
      {
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

    // Draw Pacman
    if (pacman.get_position() == curr_pos)
    {
      to_draw[1] = '@';
    }

    // Draw Ghosts
    for (const auto &pair : ghosts)
    {
      auto ghost = pair.second;
      if (ghost->get_position() == curr_pos)
      {
        to_draw[0] = toupper(ghost->get_color()[0]);
      }

      if (ghost->get_target_position() == curr_pos)
      {

        to_draw[0] = tolower(ghost->get_color()[0]);
      }
    }

    return to_draw;
  }
  // Pacman pacman;
  Blinky *blinky;
  Grid grid;

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