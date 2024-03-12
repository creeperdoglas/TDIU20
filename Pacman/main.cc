#include "full_game/YOUR_CODE_HERE/ghost.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <vector>

// Information om komplettering:
//   Kompletteringen kan gälla hela filen och alla filer i labben,
//   så får ni komplettering på en sak, kan samma sak förekomma på
//   fler ställen utan att jag skrivit det.
//
//   Komplettering lämnas in via sendlab efter senast en (1) vecka.
//
//   Har ni frågor om kompletteringen kan ni maila mig på:
//   Malte.Nilsson@liu.se

// Komplettering: Testprogrammet ska delas upp i lämpliga funktioner.
// Komplettering: Kodupprepning i kommandona för pos, dir och flytta spöken.

// Komplettering: Att alla spöken har en blinky och en inky position är orimligt.
// Komplettering: Vi vill inte behöva skicka med parametrar till t.ex get_chase_position utan all information om hur spöket ska beräkna det ska finnas internt i spöket.
// Maybe unused är inget som ingår i kursen

// Komplettering: Funktioner som inte ska överlagras ska inte vara virtuella.

// Kommentar
//  pacman & är en bättre lösning då vi alltid är beroende av pacmans position för att kunna hitta vart våran chase ska vara någonstans.
//  att låta "användaren" ansvara för att uppdatera och hålla koll på det är inte en bra design.
/// förstår, hade jag haft mer tid skulle jag även fixat detta.

// Städa upp kommentarer innan inlämning
/// fixat, har i stort sett bara kommentaren av kompileringskommandot kvar.

// Kommentar (bonus): Smart att återanvända koden från Pinky. Jag skulle dock argumentera att Inky
//   inte har med Pinky att göra och borde därför inte känna till Pinky. Det skulle vara ännu
//   snyggare att bryta ut det gemensamma till en egen funktion som båda kan använda.

// för kompilering på windows använd:  g++ .\main.cc .\given.cc .\full_game\YOUR_CODE_HERE\ghost.cc -o .\bin\pacman -I"C:\Users\Melker Gustafsson\TDIU20\Pacman"
// på laptopen, byt ut Melker Gustafsson mot boren
// Lägg till det under ifall smfl
//-I"C:/SFML-2.6.1/include" -L"C:/SFML-2.6.1/lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
// förstår intr varför min launch.json och tasks.json + cpp.properties löser det åt mig men aja .kanske förresten är för .make filen . skitsamma
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
  Pacman pacman;
  vector<Ghost *> ghosts;
  bool mode = true;
  Ghost_Tester()
      : pacman{},
        ghosts()
  {

    ghosts.push_back(new Blinky(Point{3, 3}, "red"));
    ghosts.push_back(new Pinky(Point{5, 5}, "pink"));
    ghosts.push_back(new Clyde(Point{7, 7}, "orange"));
    ghosts.push_back(new Inky(Point{1, 6}, "blue"));
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

      string color;
      string command{};
      iss >> command;

      if (command == "pos")
      {
        Point new_pos{};
        iss >> new_pos.x >> new_pos.y;
        pacman.set_position(new_pos);
      }
      else if (command == "dir")
      {
        Point new_dir{};
        iss >> new_dir.x >> new_dir.y;
        pacman.set_direction(new_dir);
      }
      else
      {
        string color = command;
        int x, y;
        iss >> x >> y;
        Point new_pos{x, y};
        for (auto &ghost : ghosts)
        {
          if (ghost->get_color() == color)
          {
            ghost->set_position(new_pos);
            break;
          }
        }
      }

      if (command == "scatter")
      {
        mode = false;
      }
      else if (command == "chase") // Assuming you add a "chase" command to explicitly switch back
      {
        mode = true;
      }
      if (command == "angry")
      {
        for (auto &ghost : ghosts)
        {

          Blinky *blinkyPtr = dynamic_cast<Blinky *>(ghost);

          // Check if the cast was successful
          if (blinkyPtr != nullptr)
          {

            blinkyPtr->set_angry(true);
            break;
          }
        }
      }
      else if (command == "quit")
      {
        for (auto &ghost : ghosts)
        {
          delete ghost;
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
  string
  to_draw(Point const &curr_pos)
  {
    string to_draw{"  "};
    Point pacmanPosition = pacman.get_position(); // för ghost då den inte är bereoende av pacman :D
    Point pacmanDirection = pacman.get_direction();
    Point blinkyPosition;
    Point pinkyPosition;
    Inky *inkyPtr = nullptr;

    for (auto &ghost : ghosts)
    {
      if (ghost->get_color() == "red")
      {
        blinkyPosition = ghost->get_position();
      }
      else if (ghost->get_color() == "pink")
      {
        pinkyPosition = ghost->get_chase_point(pacmanPosition, pacmanDirection);
      }
      else if (ghost->get_color() == "blue")
      {
        inkyPtr = dynamic_cast<Inky *>(ghost);
      }
    }
    if (inkyPtr != nullptr)
    {
      inkyPtr->set_blinky_position(blinkyPosition);
      inkyPtr->set_pinky_position(pinkyPosition);
    }

    // Draw Pacman
    if (pacman.get_position() == curr_pos)
    {
      to_draw[0] = '@';
    }
    for (const auto &ghost : ghosts)
    {
      if (mode)
      {
        if (ghost->get_chase_point(pacmanPosition, pacmanDirection) == curr_pos)
        {

          to_draw[1] = tolower(ghost->get_color()[0]);
        }
      }
      else
      {
        if (ghost->get_scatter_point(pacmanPosition) == curr_pos)
        {
          to_draw[1] = tolower(ghost->get_color()[0]);
        }
      }

      if (ghost->get_position() == curr_pos)
      {
        to_draw[0] = toupper(ghost->get_color()[0]);
      }
    }

    return to_draw;
  }

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
};

int main()
{
  Ghost_Tester gt{};
  gt.run();
  return 0;
}