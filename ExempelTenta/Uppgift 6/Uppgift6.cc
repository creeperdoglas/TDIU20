#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

#include "product.h"
#include "cart.h"

using namespace std;

int main()
{
  {
    Shopping_Cart sc{};
    sc.add_product(Product{"apelsin", 5.0}, 2);
    sc.add_product(Product{"banan", 7.5}, 5);
    sc.add_product(Product{"citron", 15.0}, 1);
    cout << sc << endl;
  }
  {
    Shopping_Cart sc{};
    sc.add_product(Product{"gurka", 9.0}, 1);
    sc.add_product(Product{"tomat", 18.5}, 5);
    sc.add_product(Product{"sallad", 11.0}, 1);
    cout << sc << endl;
  }
  {
    Shopping_Cart sc{};
    sc.add_product(Product{"apelsin", 19.0}, 1);
    sc.add_product(Product{"banan", 24.5}, 10);
    sc.add_product(Product{"citron", 48.0}, 1);
    cout << sc << endl;
  }

  return 0;
}