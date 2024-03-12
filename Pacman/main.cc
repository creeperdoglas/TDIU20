#include "full_game/YOUR_CODE_HERE/ghost.h"
// #include "SFML/Graphics.hpp"
// #include "given.h"
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


//Kommentar
// pacman & är en bättre lösning då vi alltid är beroende av pacmans position för att kunna hitta vart våran chase ska vara någonstans.
// att låta "användaren" ansvara för att uppdatera och hålla koll på det är inte en bra design.

// Städa upp kommentarer innan inlämning

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
  // map<string, Ghost *> ghosts;
  Pacman pacman;
  vector<Ghost *> ghosts;
  // Pacman pacman;
  bool mode = true;
  Ghost_Tester()
      : pacman{},
        ghosts()
  {
    // assistenten sa att vector skulle visa att man använder polymorfism mer, så kommer lägga in en kod men spara den gamla kommenterad

    ghosts.push_back(new Blinky(Point{3, 3}, "red"));
    ghosts.push_back(new Pinky(Point{5, 5}, "pink"));
    ghosts.push_back(new Clyde(Point{7, 7}, "orange"));
    ghosts.push_back(new Inky(Point{1, 6}, "blue"));

    // inky position
    // ghosts["blinky"] = new Blinky(Point{3, 3}, "red");
    // ghosts["pinky"] = new Pinky(Point{5, 5}, "pink");
    // ghosts["clyde"] = new Clyde(Point{7, 7}, "orange");
    // kan lägga till inky om jag antar att blinky och pacman börjar på samma position varje gång
    // annars skulle en specifik inky pointer behövas eller en massa nya funktioner för att inkys position ska räknas ut direkt och sedan läggas till i mapen
    // 1, -3 är inkys start position så 1,19
    // ghosts["inky"] = new Inky(Point{1, 19}, "blue");
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
      // int x, y;
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
        // string key = color + " " + to_string(x) + "," + to_string(y); // skapa unik key för varje ghost
        // if (color == "red")
        // {
        //   // cout << "red found" << endl;
        //   ghosts["blinky"]->set_position(new_pos);
        // }
        // else if (color == "pink")
        // {
        //   // cout << "pink found" << endl;
        //   ghosts["pinky"]->set_position(new_pos);
        // }
        // else if (color == "orange")
        // {
        //   // cout << "orange found" << endl;
        //   ghosts["clyde"]->set_position(new_pos);
        // }
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
    // Point blinkyPosition;
    // Point pinkyPosition;

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
    // gammal som inte funkade
    //  for (auto &ghost : ghosts)
    //  {
    //    if (ghost->get_color() == "red")
    //    {
    //      // detta verkar inte uppdatera blinky position samma med pinky, men det borde ju funka?
    //      // Point blinkyPosition = ghost->get_position();
    //      // ghost->set_blinky_position(blinkyPosition);
    //      Point blinkyPosition = ghost->get_position();
    //      Inky *inkyPtr = dynamic_cast<Inky *>(ghost);
    //      if (inkyPtr != nullptr)
    //      {
    //        inkyPtr->set_blinky_position(blinkyPosition);
    //      }
    //      break;
    //    }
    //  }
    //  for (auto &ghost : ghosts)
    //  {
    //    if (ghost->get_color() == "pink")
    //    {
    //      Point pinkyPosition = ghost->get_chase_point(pacmanPosition, pacmanDirection);
    //      // ghost->set_pinky_position(pinkyPosition);
    //      Inky *inkyPtr = dynamic_cast<Inky *>(ghost);
    //      if (inkyPtr != nullptr)
    //      {
    //        inkyPtr->set_pinky_position(pinkyPosition);
    //      }
    //    }
    //  }

    // hmm ger miljoner :/
    //  std::cout << "Inky's position: " << ghosts["inky"]->get_position().x << ", " << ghosts["inky"]->get_position().y << std::endl;

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
    // for (const auto &pair : ghosts)
    //   {
    //     auto ghost = pair.second;
    //     if (mode)
    //     {
    //       if (ghost->get_chase_point(pacmanPosition, pacmanDirection) == curr_pos)
    //       {
    //         // cout << "target found" << endl;
    //         to_draw[1] = tolower(ghost->get_color()[0]);
    //       }
    //     }
    //     else
    //     {
    //       if (ghost->get_scatter_point(pacmanPosition) == curr_pos)
    //       {
    //         // cout << "target found" << endl;
    //         to_draw[1] = tolower(ghost->get_color()[0]);
    //       }
    //     }

    //     if (ghost->get_position() == curr_pos)
    //     {
    //       // cout << "ghost found" << endl;
    //       to_draw[0] = toupper(ghost->get_color()[0]);
    //     }
    //   }
    // inky specifk, kanske bör lägga till i map
    return to_draw;
  }

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
};

int main()
{
  Ghost_Tester gt{};
  gt.run();
  return 0;
}