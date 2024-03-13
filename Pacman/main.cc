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
/// fixat

// Komplettering: Kodupprepning i kommandona för pos, dir och flytta spöken.
/// fixat, createPointFromStream används nu för att skapa en point från en istringstream, istället för 3 gånger

// Komplettering: Att alla spöken har en blinky och en inky position är orimligt.
/// fixat

// Komplettering: Vi vill inte behöva skicka med parametrar till t.ex get_chase_position utan all information om hur spöket ska beräkna det ska finnas internt i spöket.
/// fixat

// Maybe unused är inget som ingår i kursen
/// preview.redd.it/sad-hamster-v0-lc48795mb0kc1.jpeg?width=1080&crop=smart&auto=webp&s=2738b7b201a60de3d4811e0da28c2b56b0c45760
/// inget som längre behövs då get chase och scatter point inte längre tar in några parametrar

// Komplettering: Funktioner som inte ska överlagras ska inte vara virtuella.
/// antar att du menade set_position, fixat
/// tog även bort virtual från get_position i ghost.h, anledning till detta var att blinky alltid starta utanför kartan men kan lägga den manuellt utanför kartan och sedan kommer det visas på kartan (när möjligt) vart inky kommer jaga

// Kommentar
//  pacman & är en bättre lösning då vi alltid är beroende av pacmans position för att kunna hitta vart våran chase ska vara någonstans.
//  att låta "användaren" ansvara för att uppdatera och hålla koll på det är inte en bra design.
/// förstår, hade jag haft mer tid skulle jag även fixat detta.

// Städa upp kommentarer innan inlämning
/// fixat, har i stort sett bara kommentaren av kompileringskommandot kvar.

// Kommentar (bonus): Smart att återanvända koden från Pinky. Jag skulle dock argumentera att Inky
//   inte har med Pinky att göra och borde därför inte känna till Pinky. Det skulle vara ännu
//   snyggare att bryta ut det gemensamma till en egen funktion som båda kan använda.
/// fixat, tror det jag gjort nu är exakt det du menade :D

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
    ghosts.push_back(new Inky(Point{1, -3}, "blue"));
  }

  void run()
  {
    string line, command;
    while (true)
    {
      draw_map();
      cout << "> ";
      getline(cin, line);
      istringstream iss(line);
      iss >> command;
      processCommand(command, iss);
      if (command == "quit")
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
  void
  processCommand(const string &command, istringstream &iss)
  {
    if (command == "pos")
    {
      setPacmanPosition(iss);
    }
    else if (command == "dir")
    {
      setPacmanDirection(iss);
    }
    else if (command == "scatter")
    {
      mode = false;
    }
    else if (command == "chase")
    {
      mode = true;
    }
    else if (command == "angry")
    {
      setGhostsAngry();
    }
    else
    {
      setGhostPosition(command, iss);
    }
  }
  Point createPointFromStream(istringstream &iss)
  {
    int x, y;
    iss >> x >> y;
    return Point{x, y};
  }
  void setPacmanPosition(istringstream &iss)
  {
    pacman.set_position(createPointFromStream(iss));
  }

  void setPacmanDirection(istringstream &iss)
  {
    pacman.set_direction(createPointFromStream(iss));
  }

  void setGhostsAngry()
  {
    for (auto &ghost : ghosts)
    {
      if (auto *blinky = dynamic_cast<Blinky *>(ghost))
      {
        blinky->set_angry(true);
        break;
      }
    }
  }

  void setGhostPosition(const string &color, istringstream &iss)
  {
    Point new_pos = createPointFromStream(iss);
    for (auto &ghost : ghosts)
    {
      if (ghost->get_color() == color)
      {
        ghost->set_position(new_pos);
        break;
      }
    }
  }
  void updateInky()
  {
    Point blinkyPosition;
    Inky *inkyPtr = nullptr;

    for (auto &ghost : ghosts)
    {
      if (ghost->get_color() == "red")
      {
        // Antag att Blinky alltid har färgen "red"
        blinkyPosition = ghost->get_position();
      }
      else if (auto *inky = dynamic_cast<Inky *>(ghost))
      {
        inkyPtr = inky;
      }
    }

    if (inkyPtr != nullptr)
    {
      // Uppdatera Inky med Blinky's position
      inkyPtr->set_blinky_position(blinkyPosition);
    }
  }
  void updateGhosts()
  {
    Point pacmanPosition = pacman.get_position();
    Point pacmanDirection = pacman.get_direction();

    for (auto &ghost : ghosts)
    {
      ghost->update(pacmanPosition, pacmanDirection);
    }
  }

  string to_draw(Point const &curr_pos)
  {
    string to_draw{"  "};
    updateGhosts();
    updateInky();
    if (pacman.get_position() == curr_pos)
    {
      to_draw[0] = '@';
    }
    for (const auto &ghost : ghosts)
    {
      if (mode)
      {
        if (ghost->get_chase_point() == curr_pos)
        {

          to_draw[1] = tolower(ghost->get_color()[0]);
        }
      }
      else
      {
        if (ghost->get_scatter_point() == curr_pos)
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
  void
  draw_map()
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