#include <iostream>
#include <stdexcept>
class Upgift1
{
private:
  int Heltal{};
  void Check(int i) const
  {
    if (i < 15 || i > 35)
    {
      throw std::invalid_argument("Felaktigt värde");
    }
  }

public:
  Upgift1(int i) : Heltal{i}
  {
    Check(i);
  }
  int Get() const
  {
    return Heltal;
  }
  void Set(int i)
  {
    Check(i);
    Heltal = i;
  }
};
using namespace std;
int main()
{
  Upgift1 i{20};
  cout << i.Get() << endl;
  i.Set(25);
  cout << i.Get() << endl;
  Upgift1 j{5};
}
